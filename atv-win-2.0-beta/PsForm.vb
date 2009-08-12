Public Class PatchStickForm

    Private Sub PatchStickForm_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        FormFade("out")
    End Sub
    '12th August 2009 -- atv-win-2.0 beta by Sam Nazarko
    Private Sub PatchStickForm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        FormFade("in")
        'Check for updates by scraping off of google latest ver svn
        'http://atvusb-creator.googlecode.com/svn/tags/atv-win-2.0-versioning/IGNORE.txt
        Try
            Dim WebVersion As String = String.Empty
            Using UpdWebClient As New System.Net.WebClient
                WebVersion = UpdWebClient.DownloadString("http://atvusb-creator.googlecode.com/svn/tags/atv-win-2.0-versioning/IGNORE.txt")
            End Using
            Dim ServerVersion As New Version(WebVersion)
            Dim CurrentVersion As Version = My.Application.Info.Version
            If ServerVersion > CurrentVersion Then
                Dim UpdDialogRslt As DialogResult
                UpdDialogRslt = MessageBox.Show("An update is available for Apple Tv Patchstick Creator 2.0" & vbCrLf & vbCrLf & "Would you like to download it?", "Update Available", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
                If UpdDialogRslt = Windows.Forms.DialogResult.Yes Then
                    Dim ProcessProperties As New ProcessStartInfo
                    ProcessProperties.FileName = "http://code.google.com/p/atvusb-creator/downloads/list"
                    ProcessProperties.UseShellExecute = True
                    ProcessProperties.WindowStyle = ProcessWindowStyle.Maximized
                    Dim Process As Process = Process.Start(ProcessProperties)
                    Application.Exit()
                End If
            End If
        Catch
        End Try
    End Sub
    Sub FormFade(ByVal FType)
        'Form fader allows us to fade in the form or fade it out.
        Select Case FType
            Case ("in")
                Dim FadeCount As Integer
                For FadeCount = 10 To 90 Step 10
                    Me.Opacity = FadeCount / 100
                    Me.Refresh()
                    Threading.Thread.Sleep(50)
                Next
            Case ("out")
                Dim FadeCount As Integer
                For FadeCount = 90 To 10 Step -10
                    Me.Opacity = FadeCount / 100
                    Me.Refresh()
                    Threading.Thread.Sleep(50)
                Next
        End Select
        Me.Opacity = 99
    End Sub

    Private Sub CreatePatchStickBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CreatePatchStickBtn.Click
        'Sloppy code here to get round bug
        If SavePatchstickDialog.ShowDialog = DialogResult.OK Then
            Dim ImageSaveLocation As String
            ImageSaveLocation = SavePatchstickDialog.FileName
            DetermineFileSources(ImageSaveLocation)
        Else
        End If

    End Sub
    Sub DetermineFileSources(ByVal ImgLoc)
        If FwBox.Items.Contains("Custom Firmware") Then
            BuildPatchStick(ImgLoc)
        ElseIf FwBox.Items.Contains("Apple TV OS 2.4") Then
            Dim DownloadSuccess As Boolean
            'Use Item Text rather than Index to save updating every time.
            Select Case FwBox.SelectedItem
                Case "Apple TV OS 2.4"
                    DownloadSuccess = DlFirmware("http://mesu.apple.com/data/OS/061-6242.20090624.Aq20P/2Z694-5660-029.dmg")
                    If DownloadSuccess = True Then
                        BuildPatchStick(SavePatchstickDialog.FileName)
                    ElseIf DownloadSuccess = False Then
                        MessageBox.Show("An error occured downloading firmware from Apple. Please check your Internet connection and try again.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
                    End If
            End Select
        End If
    End Sub
    Private Sub CustomDMGBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CustomDMGBtn.Click
        If FindCustomDmgDialog.ShowDialog = DialogResult.OK Then
            Dim ImageOpenLocation As String
            ImageOpenLocation = FindCustomDmgDialog.FileName
            Try
                My.Computer.FileSystem.CopyFile(ImageOpenLocation, System.AppDomain.CurrentDomain.BaseDirectory(), FileIO.UIOption.AllDialogs, FileIO.UICancelOption.ThrowException)
            Catch
                MessageBox.Show("An error occured copying your custom firmware. Please check permissions and try again.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
            End Try
            FwBox.Items.Clear()
            FwBox.Items.Add("Custom Firmware")
        End If
    End Sub
    Function DlFirmware(ByVal DlUrl)
        Try
            My.Computer.Network.DownloadFile(DlUrl, System.AppDomain.CurrentDomain.BaseDirectory() & "FirmwareImage.dmg", "", "", True, 60000, True)
            Return True
        Catch
            Return False
        End Try
    End Function
    Sub BuildPatchStick(ByVal ImgLocation)
        Try
            Dim SSHToggle As Boolean
            If SSHChkBx.Checked = True Then SSHToggle = True Else If SSHChkBx.Checked = False Then SSHToggle = False
            'Write all tools to folder.
            My.Computer.FileSystem.WriteAllBytes(System.AppDomain.CurrentDomain.BaseDirectory() & "7z.exe", My.Resources.Tools._7z, False)
            My.Computer.FileSystem.WriteAllBytes(System.AppDomain.CurrentDomain.BaseDirectory() & "7z.dll", My.Resources.Tools._7z1, False)
            My.Computer.FileSystem.WriteAllBytes(System.AppDomain.CurrentDomain.BaseDirectory() & "usbit.exe", My.Resources.Tools.usbit, False)
            My.Computer.FileSystem.WriteAllBytes(System.AppDomain.CurrentDomain.BaseDirectory() & "usbit32.dll", My.Resources.Tools.usbit32, False)
            My.Computer.FileSystem.WriteAllBytes(System.AppDomain.CurrentDomain.BaseDirectory() & "injector.exe", My.Resources.Tools.injector, False)
            My.Computer.FileSystem.WriteAllText(System.AppDomain.CurrentDomain.BaseDirectory() & "FinaliseImage.bat", My.Resources.Tools.FinaliseImage, False)
            'Write the software package depending on SSH preference
            If SSHToggle = True Then
                My.Computer.FileSystem.WriteAllBytes(System.AppDomain.CurrentDomain.BaseDirectory() & "software.7z", My.Resources.Tools.atv_xbmc_ssh, False)
            ElseIf SSHToggle = False Then
                My.Computer.FileSystem.WriteAllBytes(System.AppDomain.CurrentDomain.BaseDirectory() & "software.7z", My.Resources.Tools.atv_xbmc, False)
            End If
            'Rest of script will not work until we wait for all FILES to successfully complete.
            'We wait for file transfer from OS.
            System.Threading.Thread.Sleep(2500)
            'Modify image by running bat script.
            Dim objProcess As System.Diagnostics.Process
            objProcess = New System.Diagnostics.Process()
            objProcess.StartInfo.FileName = System.AppDomain.CurrentDomain.BaseDirectory() & "FinaliseImage.bat"
            objProcess.StartInfo.WorkingDirectory = System.AppDomain.CurrentDomain.BaseDirectory()
            objProcess.StartInfo.WindowStyle = ProcessWindowStyle.Normal
            objProcess.Start()
            objProcess.WaitForExit()
            objProcess.Close()
            'Move newly formed image to desired location
            My.Computer.FileSystem.MoveFile(System.AppDomain.CurrentDomain.BaseDirectory() & "ImageFile.img", ImgLocation, FileIO.UIOption.AllDialogs, FileIO.UICancelOption.ThrowException)
            'Confirm success
            MessageBox.Show("Congratulations, your patchstick image has been created. Here are a few things to note:" & vbCrLf & vbCrLf & "If you installed SSH, your username and password is frontrow, frontrow." & vbCrLf & vbCrLf & "You should update Software Menu before installing software through it" & vbCrLf & vbCrLf & "You should update Launcher before downloading Boxee or XBMC" & vbCrLf & vbCrLf & "Thank you for using atv-win-2.0", "Patchstick Created", MessageBoxButtons.OK, MessageBoxIcon.Information)
            Dim RunUSB As DialogResult
            RunUSB = MessageBox.Show("Would you like to run USB Image Tool now?", "atv-win-2.0", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
            If RunUSB = Windows.Forms.DialogResult.Yes Then
                Shell(System.AppDomain.CurrentDomain.BaseDirectory() & "usbit.exe", AppWinStyle.NormalFocus, True)
                'TODO: Cleanup files after imaging. This might delete a backup the user creates so it's probably best to leave it.
            End If
        Catch
            MessageBox.Show("An error occured patching your firmware file. Please try again later.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End Try
    End Sub

    Private Sub AboutLnk_LinkClicked(ByVal sender As System.Object, ByVal e As System.Windows.Forms.LinkLabelLinkClickedEventArgs) Handles AboutLnk.LinkClicked
        About.Show()
    End Sub
End Class
