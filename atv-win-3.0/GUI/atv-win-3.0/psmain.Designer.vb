<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class psmain
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.WelcomeLbl = New System.Windows.Forms.Label
        Me.WelcomeBlurbLbl = New System.Windows.Forms.Label
        Me.FwGroup = New System.Windows.Forms.GroupBox
        Me.FwUrlTB = New System.Windows.Forms.TextBox
        Me.FwUrlLbl = New System.Windows.Forms.Label
        Me.CustomDmgBtn = New System.Windows.Forms.Button
        Me.FwPresetsCombo = New System.Windows.Forms.ComboBox
        Me.FwVerLbl = New System.Windows.Forms.Label
        Me.SwGroup = New System.Windows.Forms.GroupBox
        Me.SoftwareBlurbLbl = New System.Windows.Forms.Label
        Me.LauncherChkBx = New System.Windows.Forms.CheckBox
        Me.SSHChkBx = New System.Windows.Forms.CheckBox
        Me.CreatePSBtn = New System.Windows.Forms.Button
        Me.PatchstickStatusBar = New System.Windows.Forms.StatusStrip
        Me.PsStatusLbl = New System.Windows.Forms.ToolStripStatusLabel
        Me.HelpLnk = New System.Windows.Forms.LinkLabel
        Me.FindCustomDmgDialog = New System.Windows.Forms.OpenFileDialog
        Me.SavePatchstickDialog = New System.Windows.Forms.SaveFileDialog
        Me.FwGroup.SuspendLayout()
        Me.SwGroup.SuspendLayout()
        Me.PatchstickStatusBar.SuspendLayout()
        Me.SuspendLayout()
        '
        'WelcomeLbl
        '
        Me.WelcomeLbl.AutoSize = True
        Me.WelcomeLbl.Font = New System.Drawing.Font("Microsoft Sans Serif", 15.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.WelcomeLbl.Location = New System.Drawing.Point(1, 9)
        Me.WelcomeLbl.Name = "WelcomeLbl"
        Me.WelcomeLbl.Size = New System.Drawing.Size(318, 25)
        Me.WelcomeLbl.TabIndex = 0
        Me.WelcomeLbl.Text = "Apple TV Patchstick Creator 3.0"
        '
        'WelcomeBlurbLbl
        '
        Me.WelcomeBlurbLbl.Location = New System.Drawing.Point(3, 43)
        Me.WelcomeBlurbLbl.Name = "WelcomeBlurbLbl"
        Me.WelcomeBlurbLbl.Size = New System.Drawing.Size(366, 32)
        Me.WelcomeBlurbLbl.TabIndex = 1
        Me.WelcomeBlurbLbl.Text = "Welcome to Apple TV Patchstick Creator. This tool allows you to create a patchsti" & _
            "ck for  your Apple TV for all 2.x and 3.x firmwares."
        '
        'FwGroup
        '
        Me.FwGroup.Controls.Add(Me.FwUrlTB)
        Me.FwGroup.Controls.Add(Me.FwUrlLbl)
        Me.FwGroup.Controls.Add(Me.CustomDmgBtn)
        Me.FwGroup.Controls.Add(Me.FwPresetsCombo)
        Me.FwGroup.Controls.Add(Me.FwVerLbl)
        Me.FwGroup.Location = New System.Drawing.Point(6, 78)
        Me.FwGroup.Name = "FwGroup"
        Me.FwGroup.Size = New System.Drawing.Size(363, 152)
        Me.FwGroup.TabIndex = 2
        Me.FwGroup.TabStop = False
        Me.FwGroup.Text = "Firmware"
        '
        'FwUrlTB
        '
        Me.FwUrlTB.Location = New System.Drawing.Point(9, 85)
        Me.FwUrlTB.Name = "FwUrlTB"
        Me.FwUrlTB.Size = New System.Drawing.Size(348, 20)
        Me.FwUrlTB.TabIndex = 4
        '
        'FwUrlLbl
        '
        Me.FwUrlLbl.AutoSize = True
        Me.FwUrlLbl.Location = New System.Drawing.Point(6, 60)
        Me.FwUrlLbl.Name = "FwUrlLbl"
        Me.FwUrlLbl.Size = New System.Drawing.Size(74, 13)
        Me.FwUrlLbl.TabIndex = 3
        Me.FwUrlLbl.Text = "Firmware URL"
        '
        'CustomDmgBtn
        '
        Me.CustomDmgBtn.Location = New System.Drawing.Point(252, 120)
        Me.CustomDmgBtn.Name = "CustomDmgBtn"
        Me.CustomDmgBtn.Size = New System.Drawing.Size(105, 26)
        Me.CustomDmgBtn.TabIndex = 2
        Me.CustomDmgBtn.Text = "Choose DMG"
        Me.CustomDmgBtn.UseVisualStyleBackColor = True
        '
        'FwPresetsCombo
        '
        Me.FwPresetsCombo.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.FwPresetsCombo.FormattingEnabled = True
        Me.FwPresetsCombo.Items.AddRange(New Object() {"Apple TV OS 3.0.1"})
        Me.FwPresetsCombo.Location = New System.Drawing.Point(109, 25)
        Me.FwPresetsCombo.Name = "FwPresetsCombo"
        Me.FwPresetsCombo.Size = New System.Drawing.Size(137, 21)
        Me.FwPresetsCombo.TabIndex = 1
        '
        'FwVerLbl
        '
        Me.FwVerLbl.AutoSize = True
        Me.FwVerLbl.Location = New System.Drawing.Point(6, 28)
        Me.FwVerLbl.Name = "FwVerLbl"
        Me.FwVerLbl.Size = New System.Drawing.Size(87, 13)
        Me.FwVerLbl.TabIndex = 0
        Me.FwVerLbl.Text = "Firmware Version"
        '
        'SwGroup
        '
        Me.SwGroup.Controls.Add(Me.SoftwareBlurbLbl)
        Me.SwGroup.Controls.Add(Me.LauncherChkBx)
        Me.SwGroup.Controls.Add(Me.SSHChkBx)
        Me.SwGroup.Location = New System.Drawing.Point(6, 247)
        Me.SwGroup.Name = "SwGroup"
        Me.SwGroup.Size = New System.Drawing.Size(363, 79)
        Me.SwGroup.TabIndex = 3
        Me.SwGroup.TabStop = False
        Me.SwGroup.Text = "Software"
        '
        'SoftwareBlurbLbl
        '
        Me.SoftwareBlurbLbl.AutoSize = True
        Me.SoftwareBlurbLbl.Location = New System.Drawing.Point(6, 26)
        Me.SoftwareBlurbLbl.Name = "SoftwareBlurbLbl"
        Me.SoftwareBlurbLbl.Size = New System.Drawing.Size(245, 13)
        Me.SoftwareBlurbLbl.TabIndex = 6
        Me.SoftwareBlurbLbl.Text = "Please select the software you would like to install."
        '
        'LauncherChkBx
        '
        Me.LauncherChkBx.AutoSize = True
        Me.LauncherChkBx.Location = New System.Drawing.Point(130, 52)
        Me.LauncherChkBx.Name = "LauncherChkBx"
        Me.LauncherChkBx.Size = New System.Drawing.Size(71, 17)
        Me.LauncherChkBx.TabIndex = 4
        Me.LauncherChkBx.Text = "Launcher"
        Me.LauncherChkBx.UseVisualStyleBackColor = True
        '
        'SSHChkBx
        '
        Me.SSHChkBx.AutoSize = True
        Me.SSHChkBx.Location = New System.Drawing.Point(9, 52)
        Me.SSHChkBx.Name = "SSHChkBx"
        Me.SSHChkBx.Size = New System.Drawing.Size(48, 17)
        Me.SSHChkBx.TabIndex = 0
        Me.SSHChkBx.Text = "SSH"
        Me.SSHChkBx.UseVisualStyleBackColor = True
        '
        'CreatePSBtn
        '
        Me.CreatePSBtn.Location = New System.Drawing.Point(6, 332)
        Me.CreatePSBtn.Name = "CreatePSBtn"
        Me.CreatePSBtn.Size = New System.Drawing.Size(124, 31)
        Me.CreatePSBtn.TabIndex = 4
        Me.CreatePSBtn.Text = "Create Patchstick"
        Me.CreatePSBtn.UseVisualStyleBackColor = True
        '
        'PatchstickStatusBar
        '
        Me.PatchstickStatusBar.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.PsStatusLbl})
        Me.PatchstickStatusBar.Location = New System.Drawing.Point(0, 374)
        Me.PatchstickStatusBar.Name = "PatchstickStatusBar"
        Me.PatchstickStatusBar.Size = New System.Drawing.Size(378, 22)
        Me.PatchstickStatusBar.TabIndex = 5
        '
        'PsStatusLbl
        '
        Me.PsStatusLbl.Name = "PsStatusLbl"
        Me.PsStatusLbl.Size = New System.Drawing.Size(39, 17)
        Me.PsStatusLbl.Text = "Status"
        '
        'HelpLnk
        '
        Me.HelpLnk.AutoSize = True
        Me.HelpLnk.Font = New System.Drawing.Font("Microsoft Sans Serif", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.HelpLnk.Location = New System.Drawing.Point(349, 339)
        Me.HelpLnk.Name = "HelpLnk"
        Me.HelpLnk.Size = New System.Drawing.Size(20, 24)
        Me.HelpLnk.TabIndex = 6
        Me.HelpLnk.TabStop = True
        Me.HelpLnk.Text = "?"
        '
        'FindCustomDmgDialog
        '
        Me.FindCustomDmgDialog.Filter = "Apple TV Firmware Files|*.dmg"
        '
        'SavePatchstickDialog
        '
        Me.SavePatchstickDialog.Filter = "Apple Patchstick Images | *.img"
        '
        'psmain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(378, 396)
        Me.Controls.Add(Me.HelpLnk)
        Me.Controls.Add(Me.PatchstickStatusBar)
        Me.Controls.Add(Me.CreatePSBtn)
        Me.Controls.Add(Me.SwGroup)
        Me.Controls.Add(Me.FwGroup)
        Me.Controls.Add(Me.WelcomeBlurbLbl)
        Me.Controls.Add(Me.WelcomeLbl)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.MaximizeBox = False
        Me.Name = "psmain"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "Apple TV Patchstick Creator"
        Me.FwGroup.ResumeLayout(False)
        Me.FwGroup.PerformLayout()
        Me.SwGroup.ResumeLayout(False)
        Me.SwGroup.PerformLayout()
        Me.PatchstickStatusBar.ResumeLayout(False)
        Me.PatchstickStatusBar.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents WelcomeLbl As System.Windows.Forms.Label
    Friend WithEvents WelcomeBlurbLbl As System.Windows.Forms.Label
    Friend WithEvents FwGroup As System.Windows.Forms.GroupBox
    Friend WithEvents FwVerLbl As System.Windows.Forms.Label
    Friend WithEvents FwPresetsCombo As System.Windows.Forms.ComboBox
    Friend WithEvents CustomDmgBtn As System.Windows.Forms.Button
    Friend WithEvents FwUrlLbl As System.Windows.Forms.Label
    Friend WithEvents FwUrlTB As System.Windows.Forms.TextBox
    Friend WithEvents SwGroup As System.Windows.Forms.GroupBox
    Friend WithEvents SSHChkBx As System.Windows.Forms.CheckBox
    Friend WithEvents LauncherChkBx As System.Windows.Forms.CheckBox
    Friend WithEvents SoftwareBlurbLbl As System.Windows.Forms.Label
    Friend WithEvents CreatePSBtn As System.Windows.Forms.Button
    Friend WithEvents PatchstickStatusBar As System.Windows.Forms.StatusStrip
    Friend WithEvents PsStatusLbl As System.Windows.Forms.ToolStripStatusLabel
    Friend WithEvents HelpLnk As System.Windows.Forms.LinkLabel
    Friend WithEvents FindCustomDmgDialog As System.Windows.Forms.OpenFileDialog
    Friend WithEvents SavePatchstickDialog As System.Windows.Forms.SaveFileDialog

End Class
