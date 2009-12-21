'atv-win-3.0 -- Sam Nazarko
'Last Build: 21/12/2009

'//
'#########################################################################################################
'I have done my best to comment everything so it is clear what is going on at each stage. If you are still 
'confused about something feel free to email me at samnazarko [AT] stmteam.com. 
'#########################################################################################################
'//

'Efficiency and a whole lot less head scratching with:
Option Explicit On
Option Strict On

Imports System.Text.RegularExpressions

Public Class psmain

    Dim PsSuccess_bn As Boolean
    'Dim PsSuccess_bn as subjective ;)

    Private Sub psmain_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load

        '--------------------------------------Prepare application--------------------------------------

        '#FADEIN (1)
        'Nice form fading effect (call fade-subroutine)
        FormFade(True)

        '#TOOLTIPS (2)
        'Set some tooltips for the Firmware Groupbox to make the user understand things a bit better :)
        'Create the tooltips
        Dim FwPresetsCombo_TT As New ToolTip
        Dim FwURLTb_TT As New ToolTip
        Dim CustomDmgBtn_TT As New ToolTip
        Dim SSHChkBx_TT As New ToolTip
        Dim LauncherChkBx_TT As New ToolTip
        'Set the tooltips
        FwPresetsCombo_TT.SetToolTip(FwPresetsCombo, "Select firmware version to pre-populate firmware URL box")
        FwURLTb_TT.SetToolTip(FwUrlTB, "Enter a custom URL here if trying to download an old firmware")
        CustomDmgBtn_TT.SetToolTip(CustomDmgBtn, "Create a patchstick from firmware on your hard drive")
        SSHChkBx_TT.SetToolTip(SSHChkBx, "SSH allows you to upload files and send commands to your Apple TV")
        LauncherChkBx_TT.SetToolTip(LauncherChkBx, "Launcher brings you XBMC and Boxee")
        'Activate the tooltips
        FwPresetsCombo_TT.Active = True
        FwURLTb_TT.Active = True
        CustomDmgBtn_TT.Active = True
        SSHChkBx_TT.Active = True
        LauncherChkBx_TT.Active = True

        '#SET CONTROL PROPERTIES (3)
        CustomDmgBtn.Text = "Choose DMG"
        PsStatusLbl.Text = "Ready"

        '#UPDATE CHECKING (4)
        'Check for updates by scraping off of Google Code SVN
        ' 5/12/09 00:00 (strange time) - location changed for 3.0 version, update info in versioning directory of the trunk, tag is not needed.
        'As of December, using: http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/Versioning/latest.dat

        'Things I'm aware of:

        '#--
        'People have wondered why I do not just update the executable and why I open the downloads page instead. Put simply,
        'it's because I'm not evil. I would like to present the user with the list of downloads and provide them with information
        'rather than simply download an EXE which terminates the application they are using, updates the patchstick files and restarts
        'it without their consent/knowledge. 
        '#--

        '#--
        'This application does not check for a network connection before checking for updates. This is because the worst case scenario is
        'that the error handler is triggered. The user is not informed of an update, even if there is one, it will just check next time.
        'However THEY should have an active internet connection to download the resources and firmware files needed.
        '#--

        '^ questions via email answered on 14/09/09


        Try
            Dim WebVersion As String = String.Empty
            Using UpdWebClient As New System.Net.WebClient
                'Download a file containing the latest version number.
                WebVersion = UpdWebClient.DownloadString("http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/Versioning/latest.dat")
            End Using
            Dim ServerVersion As New Version(WebVersion)
            'Harvest the version number of the current patchstick app. Stored in project information.
            Dim CurrentVersion As Version = My.Application.Info.Version
            'Compare. If the web reports a greater version than the current one, we inform the user of a new version.
            If ServerVersion > CurrentVersion Then
                Dim UpdDialogRslt As DialogResult
                UpdDialogRslt = MessageBox.Show("An update is available for Apple Tv Patchstick Creator" & vbCrLf & vbCrLf & "Would you like to download it?", "Update Available", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
                If UpdDialogRslt = Windows.Forms.DialogResult.Yes Then
                    'If they say yes we open the downloads page of atv-usb-creator in the default browser.
                    Dim ProcessProperties As New ProcessStartInfo
                    ProcessProperties.FileName = "http://code.google.com/p/atvusb-creator/downloads/list"
                    ProcessProperties.UseShellExecute = True
                    ProcessProperties.WindowStyle = ProcessWindowStyle.Maximized
                    Dim Process As Process = Process.Start(ProcessProperties)
                    'We then close the application so replacing/removing the old one is easy as pie.
                    Application.Exit()
                End If
            End If
        Catch
        End Try

        '#DONE
        'Everything needed to start is done. We should be up. 

        '</--------------------------------------Prepare application--------------------------------------

    End Sub
    Private Sub psmain_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing

        '--------------------------------------Post-processing application events--------------------------------------

        '#FADEOUT -0
        'Nice form fading effect (call fade-subroutine)
        FormFade(False)

    End Sub

    Sub FormFade(ByVal FadeIn As Boolean)
        'Form fader allows us to fade in the form or fade it out.
        '5/12/09 00:17 - got rid of ByVal FType where case selection was either "in" or "out" and used boolean values to
        'maximise efficiency and comply with Opt.Strict. True is now fadein, false is now fadeout.

        Select Case FadeIn
            Case True
                Dim FadeCount As Integer
                'Loop to increase opacity in stages of 10.
                For FadeCount = 10 To 90 Step 10
                    Me.Opacity = FadeCount / 100
                    'Update the form. Like DoEvents but cosmetically.
                    Me.Refresh()
                    'Pause for 50 milliseconds, so we've got a gradual fade.
                    Threading.Thread.Sleep(50)
                Next
                '5/12/09 18:13 - Setting to 101 gets rid of fade effect completely. Gets rid of wasted resources on opacity.
                Me.Opacity = 101
            Case False
                Dim FadeCount As Integer
                'Loop to decrease opacity in stages of 10.
                For FadeCount = 90 To 10 Step -10
                    Me.Opacity = FadeCount / 100
                    'Update the form. Like DoEvents but cosmetically.
                    Me.Refresh()
                    'Pause for 50 milliseconds, so we've got a gradual fade.
                    Threading.Thread.Sleep(50)
                Next
                '5/12/2009 18:14 - Set this to 0 and enjoy a better transition.
                Me.Opacity = 0
        End Select
        '5/12/09 18:17 - Improved fade effect by editing opacity values. Better transition and better resource consumption.

    End Sub

    Private Sub CustomDmgBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CustomDmgBtn.Click
        'Simple onclick decider. We cannot change a button's onclick properties dynamically, so instead we decide what we're doing
        'based on it's text. 
        If CustomDmgBtn.Text = "Choose DMG" Then ToggleHandlerSR(True) Else If CustomDmgBtn.Text = "Use Wizard" Then ToggleHandlerSR(False)
        '5/12/2009 18:58 - We are only using two options here. Let's be more efficient and use boolean. True=custom-dmg;False=wizard.
        'If when the button is clicked the text says "Choose DMG" then the user wants to choose a custom firmware, so we bring up
        'the custom dialogue box. If however it says "Use Wizard" then we re-enable the firmware box and url box so the user can select
        'a firmware preset.
    End Sub
    Private Sub ToggleHandlerSR(ByVal CustomDMG As Boolean)
        'If this is triggered it means user has selected the Custom DMG feature.
        If CustomDMG = True Then
            'Disable the presets box
            FwPresetsCombo.Enabled = False
            'and the firmware URL box
            FwUrlTB.Enabled = False
            'Here we have to clear an item because we add "Custom Firmware" to the box to the box when we are using the 
            'Choose DMG feature
            FwPresetsCombo.Items.Clear()
            'Set the text to Use Wizard so it can be toggled back.
            CustomDmgBtn.Text = "Use Wizard"
            'Continue thru custom firmware proceedure by calling new subroutine.
            PrepCustomSR()
        Else
            'If this is triggered it means user has reverted to the wizard feature. 
            If CustomDMG = False Then
                'Enable the presets box
                FwPresetsCombo.Enabled = True
                'and the firmware URL box
                FwUrlTB.Enabled = True
                'Here we have to clear an item because we add "Custom Firmware" to the box to the box when we are using the 
                'Choose DMG feature
                FwPresetsCombo.Items.Clear()
                'We then have to add the firmware(s) back as an option. [3.0.1 at time of writing]
                FwPresetsCombo.Items.Add("Apple TV OS 3.0.1")
                'Set the text to Choose DMG so it can be toggled back.
                CustomDmgBtn.Text = "Choose DMG"
            End If
        End If
    End Sub

    Private Sub PrepCustomSR()
        Dim PrepCustomSuccess As Boolean
        'We need to check if this is successful or we will get a huge bug where the user is able to run the patchstick creation
        'without the core firmware file being present.
        If FindCustomDmgDialog.ShowDialog = DialogResult.OK Then
            'Get file location info.
            Dim ImageOpenLocation As String
            ImageOpenLocation = FindCustomDmgDialog.FileName
            'Try and copy the files to the working dir.
            Try
                'While we try this let's inform the person we're doing something with the Windows file gui.
                'Disable patchstick creation button (can't have them able to create a PS before atv-win is ready.)
                CreatePSBtn.Enabled = False
                'Change status bar text
                PsStatusLbl.Text = "Copying files, please wait..."
                My.Computer.FileSystem.CopyFile(ImageOpenLocation.ToString, System.AppDomain.CurrentDomain.BaseDirectory & "FirmwareImage.dmg", FileIO.UIOption.AllDialogs, FileIO.UICancelOption.ThrowException)
                'Log success.
                'Re-enable Create Patchstick button
                CreatePSBtn.Enabled = True
                'Set Status Label back to Ready
                PsStatusLbl.Text = "Ready"
                PrepCustomSuccess = True
            Catch
                'Show failure message.
                MessageBox.Show("An error occured copying your custom firmware. Please check permissions and try again.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
                'Log failure.
                PrepCustomSuccess = False
            End Try
        Else
            'If the user cancels the dialog we must return to the wizard we must log this is an error. This is to avoid
            'the bug discussed previously.
            If DialogResult = Not DialogResult.OK Then
                'We would have disable the PS btn previously, let's guarantee it's re-enabled.
                CreatePSBtn.Enabled = True
                'And reset the status bar too
                PsStatusLbl.Text = "Ready"
                PrepCustomSuccess = False
            End If
        End If
        'If this proceedure is not successful,
        If PrepCustomSuccess = False Then
            'Go back to wizard mode.
            ToggleHandlerSR(False)
        End If

    End Sub
    Sub DetermineFileSources(ByVal ImgLoc As String)
        If FwPresetsCombo.Enabled = False Then
            'If custom FW has been chosen we just skip right to the patchstick creation process.
            BuildPatchStick(ImgLoc)
        ElseIf FwPresetsCombo.Enabled = True Then
            'Else we are going to need to download the latest FW.
            Dim DownloadSuccess As Boolean
            DownloadSuccess = DlFirmware(FwUrlTB.Text)
            'If download was ok we build the patchstick.
            If DownloadSuccess = True Then
                BuildPatchStick(SavePatchstickDialog.FileName)
                'If it was not we display an error message and go back to wizard mode to avoid critical bug.
            ElseIf DownloadSuccess = False Then
                MessageBox.Show("An error occured downloading firmware from Apple. Please check your Internet connection and try again.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
                ToggleHandlerSR(False)
            End If
        End If
    End Sub
    Function DlFirmware(ByVal DlUrl As String) As Boolean
        Try
            'Try and download firmware specified.
            'Set status bar text
            PsStatusLbl.Text = "Downloading firmware, please wait..."
            My.Computer.Network.DownloadFile(DlUrl, System.AppDomain.CurrentDomain.BaseDirectory() & "FirmwareImage.dmg", "", "", True, 60000, True)
            'If it worked we return True.
            'And reset the status bar
            PsStatusLbl.Text = "Ready"
            Return True
        Catch
            'If it went wrong we return False.
            'Make sure the statusbar reverts.
            PsStatusLbl.Text = "Ready"
            'And the Create Patchstick button is re-enabled.
            CreatePSBtn.Enabled = True
            Return False
        End Try
    End Function
    Function DlResources(ByVal DlUrl As String, ByVal FileName As String) As Boolean
        'This is the DlResources function. Allows user to specify file to save as and executes GUI download unlike
        'DlFirmware() where the files are much bigger.
        'Showing GUI necessary to stop form hanging. Not pretty. At some point I will create a downloading class.
        Try
            'Resources are DOWNLOADED every time even if they already exist. This is to make sure they are the latest ver.
            My.Computer.Network.DownloadFile(DlUrl, System.AppDomain.CurrentDomain.BaseDirectory() & FileName, "", "", True, 60000, True)
            Return True
        Catch
            Return False
        End Try
    End Function

    Sub BuildPatchStick(ByVal ImgLocation As String)
        'Determine what software is to be included in patchstick. 
        'To do this we assign each package a number. The total number tells us what is to be installed.
        Dim PackagesNum As Integer
        'HAVE TO SET THIS TO 0 or creating another patchstick will keep the old number and really mess things up.
        PackagesNum = 0
        '//SSH = 2
        '//Launcher = 4
        If SSHChkBx.Checked = True Then PackagesNum = PackagesNum + 2
        If LauncherChkBx.Checked = True Then PackagesNum = PackagesNum + 4
        '5/12/09 15:31 ## bin utils always installed and software menu is now EOL.
        'We only want to download the image we want, so we now decide which one we are going to pull of SVN.
        Dim ImageURL As String
        Select Case PackagesNum
            Case 2 'SSH only
                ImageURL = "http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/WebDep/Images/atv-ssh.7z"
            Case 4 ' Launcher only
                ImageURL = "http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/WebDep/Images/atv-xbmc.7z"
            Case 6 ' SSH and Launcher - how it should be ;)
                ImageURL = "http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/WebDep/Images/atv-xbmc-ssh.7z"
            Case Else
                'Prevent null-ref
                Application.Exit()
        End Select
        'Measure download success
        Dim DownloadSuccess As Boolean = True
        'Pull down the other resources alongside this. Put them all in the working directory.
        'Download desired image.
        PsStatusLbl.Text = "Downloading aTV software..."
        If DlResources(ImageURL, "SoftwareImage.7z") = False Then DownloadSuccess = False
        'Download 7zip command line util.
        PsStatusLbl.Text = "Downloading 7z..."
        If DlResources("http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/WebDep/Tools/7z.exe", "7z.exe") = False Then DownloadSuccess = False
        If DlResources("http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/WebDep/Tools/7z.dll", "7z.dll") = False Then DownloadSuccess = False
        'Download boot.efi injector
        PsStatusLbl.Text = "Downloading injector..."
        If DlResources("http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/WebDep/Tools/injector.exe", "injector.exe") = False Then DownloadSuccess = False
        'Download USB Image Tool
        PsStatusLbl.Text = "Downloading usbit..."
        If DlResources("http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/WebDep/Tools/usbit.exe", "usbit.exe") = False Then DownloadSuccess = False
        If DlResources("http://atvusb-creator.googlecode.com/svn/trunk/atv-win-3.0/WebDep/Tools/usbit32.dll", "usbit32.dll") = False Then DownloadSuccess = False
        'If any download has failed we will fail the patchstick
        If DownloadSuccess = False Then
            FailBuildPatchstick()
        Else
            'Else we continue building it.
            Try
                'If we've got to here all downloads are done.
                '###########################################################################################################
                '5/12/09 16:25 - Was planning to use StreamReader and StreamWriter pipes and redirect everything through CMD, 
                'however it is impossible to correctly tell when the process has ended.
                'This is because HasExited and WaitForExit have false readings due to CMD parsing new windows even with
                '/b, /d. We can't monitor sep.threads so easily -- email me for more info. 
                '###########################################################################################################
                '12/12/09 23:17 - Result of no redirected output/input is that we have to use old batch technique.
                'Set status
                PsStatusLbl.Text = "Manipulating patchstick images..."
                'Create a new process
                Dim objProcess As New System.Diagnostics.Process
                'Set the file to the CMDlet that we have.
                objProcess.StartInfo.FileName = System.AppDomain.CurrentDomain.BaseDirectory() & "FinaliseImage.cmd"
                'Set the current directory as local directory (equiv to 'CD' but is dynamic)
                objProcess.StartInfo.WorkingDirectory = System.AppDomain.CurrentDomain.BaseDirectory()
                'Don't show yourself.
                objProcess.StartInfo.WindowStyle = ProcessWindowStyle.Hidden
                'Grab workflow CMDlet we are about to start.
                My.Computer.FileSystem.WriteAllText(System.AppDomain.CurrentDomain.BaseDirectory() & "FinaliseImage.cmd", My.Resources.Workflow, False)
                'Fire
                objProcess.Start()
                'Wait for it to finish before we attempt to continue.
                objProcess.WaitForExit()
                'Clear obj and return mem.
                objProcess.Close()
                'Move newly formed image to desired location
                My.Computer.FileSystem.MoveFile(System.AppDomain.CurrentDomain.BaseDirectory() & "ImageFile.img", ImgLocation, FileIO.UIOption.AllDialogs, FileIO.UICancelOption.ThrowException)
                PsSuccess_bn = True
            Catch
                PsSuccess_bn = False
            End Try
            PsStatusLbl.Text = "Ready"
            If PsSuccess_bn = True Then
                'If we're here, PS Creation was a success.
                'Confirm success
                'Declare a var for the confirmation message
                Dim ConfirmMessage As String
                'And write it line by line so it is easy for us to read.
                ConfirmMessage = "Congratulations, your patchstick image has been created. Here are a few things to note:" & vbCrLf & vbCrLf
                'If SSH was installed we will include information about SSH.
                If SSHChkBx.Checked = True Then
                    ConfirmMessage = ConfirmMessage & "You installed SSH. The distribution is now OpenSSH which replaces dropbear. Your username and password is frontrow, frontrow." & vbCrLf & vbCrLf
                End If
                ConfirmMessage = ConfirmMessage & "Software Menu is now discontinued." & vbCrLf & vbCrLf
                'If Launcher was installed we will tell them to update it.
                If LauncherChkBx.Checked = True Then
                    ConfirmMessage = ConfirmMessage & "You should update Launcher before downloading Boxee or XBMC" & vbCrLf & vbCrLf
                End If
                ConfirmMessage = ConfirmMessage & "Thank you for using Apple TV Patchstick Creator for Windows 3.0"
                MessageBox.Show(ConfirmMessage, "Patchstick Created", MessageBoxButtons.OK, MessageBoxIcon.Information)
                Dim RunUSB As DialogResult
                RunUSB = MessageBox.Show("Would you like to run USB Image Tool now?", "Apple TV Patchstick Creator", MessageBoxButtons.YesNo, MessageBoxIcon.Question)
                Try
                    If RunUSB = Windows.Forms.DialogResult.Yes Then
                        Shell(System.AppDomain.CurrentDomain.BaseDirectory() & "usbit.exe", AppWinStyle.NormalFocus, True)
                    End If
                Catch
                    MessageBox.Show("Could not run USB Image Tool", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
                End Try
                'Potentially could cleanup files after imaging. However this COULD delete an image the user has left for backup so make it there own responsibility.
                If PsSuccess_bn = True Then MessageBox.Show("You can now delete all the files in the directory that you run Apple TV Patchstick Creator from if you have not created a backup with Usb Image Tool.", "Cleanup Information", MessageBoxButtons.OK, MessageBoxIcon.Information)
                'Re-enable ps btn
                CreatePSBtn.Enabled = True
            Else
                FailBuildPatchstick()
            End If
        End If
    End Sub

    Private Sub FailBuildPatchstick()
        'If something goes wrong during BuildPatchstick() we call this sub.
        MessageBox.Show("An error occured creating your patchstick. Please check your Internet Connection and try again.", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error)
        'Re-enable PS btn so they can have another go.
        CreatePSBtn.Enabled = True
        'Set status labels back
        PsStatusLbl.Text = "Ready"
    End Sub

    Private Sub CreatePSBtn_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CreatePSBtn.Click
        'Make sure a couple of prerequisites are met.
        'Evaluate the FW url box with a RegEx and make sure it is a legitimately formulated URL. 
        'Must be a domain name or IP, [protocols: FTP/HTTP] + port num. 5/12/09 15:21 - decided to remove requirement for file 
        'to have a ".dmg" extension.
        If Regex.IsMatch(FwUrlTB.Text, "(?:(?:(?:http|ftp)://)(?:w{3}\.)?(?:[a-zA-Z0-9/;\?&=:\-_\$\+!\*'\(\|\\~\[\]#%\.])+)") = True Or FwPresetsCombo.Enabled = False Then
            'Make sure either Launcher or SSH is checked.
            If SSHChkBx.Checked = True Or LauncherChkBx.Checked = True Then
                'Ask the user where they would like to save their patchstick image.
                If SavePatchstickDialog.ShowDialog = DialogResult.OK Then
                    Dim ImageSaveLocation As String
                    ImageSaveLocation = SavePatchstickDialog.FileName
                    'Disable button temporarily so the user is aware patchstick creation is underway
                    CreatePSBtn.Enabled = False
                    DetermineFileSources(ImageSaveLocation)
                Else
                End If
                'They didn't enter a (valid) url. Inform the user and halt the process.
            Else
                MessageBox.Show("You must install software on the Apple TV.", "An error occured", MessageBoxButtons.OK, MessageBoxIcon.Error)
            End If
        Else : MessageBox.Show("Please ensure a valid URL is entered in the Firmware URL box.", "An error occured", MessageBoxButtons.OK, MessageBoxIcon.Error)
        End If
    End Sub

    Private Sub FwPresetsCombo_SelectedValueChanged(ByVal sender As Object, ByVal e As System.EventArgs) Handles FwPresetsCombo.SelectedIndexChanged
        '6/12/09 14:54 - Case selection is now moved from DetermineFileSources. Here we prepopulate the FW url box based on the user's 
        'firmware choice.
        Select Case FwPresetsCombo.SelectedItem.ToString ' .ToString = opt.strict compliant.
            Case "Apple TV OS 3.0.1"
                FwUrlTB.Text = "http://mesu.apple.com/data/OS/061-7491.20091107.TVA31/2Z694-6004-003.dmg"
            Case Else
                MsgBox(FwPresetsCombo.SelectedText)
        End Select
    End Sub

    Private Sub HelpLnk_LinkClicked(ByVal sender As System.Object, ByVal e As System.Windows.Forms.LinkLabelLinkClickedEventArgs) Handles HelpLnk.LinkClicked
        'Use ShellExec to open the atvWindowsGuide in the user's default browser.
        Dim ProcessProperties As New ProcessStartInfo
        ProcessProperties.FileName = "http://code.google.com/p/atvusb-creator/wiki/atvWindowsGuide"
        ProcessProperties.UseShellExecute = True
        ProcessProperties.WindowStyle = ProcessWindowStyle.Maximized
        Dim Process As Process = Process.Start(ProcessProperties)
    End Sub
End Class
