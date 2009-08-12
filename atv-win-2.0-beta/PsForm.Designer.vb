<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class PatchStickForm
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
        Me.AboutLnk = New System.Windows.Forms.LinkLabel
        Me.Label1 = New System.Windows.Forms.Label
        Me.WelcomeLbl = New System.Windows.Forms.Label
        Me.FwVerLbl = New System.Windows.Forms.Label
        Me.FwBox = New System.Windows.Forms.ComboBox
        Me.FirmwareGroup = New System.Windows.Forms.GroupBox
        Me.CustomDMGBtn = New System.Windows.Forms.Button
        Me.SoftwareInstallationsGroup = New System.Windows.Forms.GroupBox
        Me.Label2 = New System.Windows.Forms.Label
        Me.LauncherChkBx = New System.Windows.Forms.CheckBox
        Me.SftwareMnuChkBx = New System.Windows.Forms.CheckBox
        Me.SSHChkBx = New System.Windows.Forms.CheckBox
        Me.CreatePatchStickBtn = New System.Windows.Forms.Button
        Me.FindCustomDmgDialog = New System.Windows.Forms.OpenFileDialog
        Me.SavePatchstickDialog = New System.Windows.Forms.SaveFileDialog
        Me.FirmwareGroup.SuspendLayout()
        Me.SoftwareInstallationsGroup.SuspendLayout()
        Me.SuspendLayout()
        '
        'AboutLnk
        '
        Me.AboutLnk.AutoSize = True
        Me.AboutLnk.Location = New System.Drawing.Point(319, 327)
        Me.AboutLnk.Name = "AboutLnk"
        Me.AboutLnk.Size = New System.Drawing.Size(13, 13)
        Me.AboutLnk.TabIndex = 0
        Me.AboutLnk.TabStop = True
        Me.AboutLnk.Text = "?"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Font = New System.Drawing.Font("Arial", 18.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.ForeColor = System.Drawing.Color.DodgerBlue
        Me.Label1.Location = New System.Drawing.Point(3, 9)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(112, 27)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "Welcome"
        '
        'WelcomeLbl
        '
        Me.WelcomeLbl.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.WelcomeLbl.ForeColor = System.Drawing.Color.DodgerBlue
        Me.WelcomeLbl.Location = New System.Drawing.Point(5, 47)
        Me.WelcomeLbl.Name = "WelcomeLbl"
        Me.WelcomeLbl.Size = New System.Drawing.Size(335, 56)
        Me.WelcomeLbl.TabIndex = 2
        Me.WelcomeLbl.Text = "Welcome to the Apple Patchstick Creator 2.0. This tool allows you to create a pat" & _
            "chstick quickly and easily for all current 2.x firmwares."
        '
        'FwVerLbl
        '
        Me.FwVerLbl.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FwVerLbl.ForeColor = System.Drawing.Color.DodgerBlue
        Me.FwVerLbl.Location = New System.Drawing.Point(2, 36)
        Me.FwVerLbl.Name = "FwVerLbl"
        Me.FwVerLbl.Size = New System.Drawing.Size(115, 20)
        Me.FwVerLbl.TabIndex = 3
        Me.FwVerLbl.Text = "Firmware Version:"
        '
        'FwBox
        '
        Me.FwBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.FwBox.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.FwBox.FormattingEnabled = True
        Me.FwBox.Items.AddRange(New Object() {"Apple TV OS 2.4"})
        Me.FwBox.Location = New System.Drawing.Point(123, 35)
        Me.FwBox.Name = "FwBox"
        Me.FwBox.Size = New System.Drawing.Size(159, 22)
        Me.FwBox.TabIndex = 4
        '
        'FirmwareGroup
        '
        Me.FirmwareGroup.Controls.Add(Me.CustomDMGBtn)
        Me.FirmwareGroup.Controls.Add(Me.FwBox)
        Me.FirmwareGroup.Controls.Add(Me.FwVerLbl)
        Me.FirmwareGroup.Location = New System.Drawing.Point(12, 106)
        Me.FirmwareGroup.Name = "FirmwareGroup"
        Me.FirmwareGroup.Size = New System.Drawing.Size(320, 99)
        Me.FirmwareGroup.TabIndex = 5
        Me.FirmwareGroup.TabStop = False
        Me.FirmwareGroup.Text = "Firmware"
        '
        'CustomDMGBtn
        '
        Me.CustomDMGBtn.Location = New System.Drawing.Point(220, 68)
        Me.CustomDMGBtn.Name = "CustomDMGBtn"
        Me.CustomDMGBtn.Size = New System.Drawing.Size(94, 25)
        Me.CustomDMGBtn.TabIndex = 8
        Me.CustomDMGBtn.Text = "Custom DMG"
        Me.CustomDMGBtn.UseVisualStyleBackColor = True
        '
        'SoftwareInstallationsGroup
        '
        Me.SoftwareInstallationsGroup.Controls.Add(Me.Label2)
        Me.SoftwareInstallationsGroup.Controls.Add(Me.LauncherChkBx)
        Me.SoftwareInstallationsGroup.Controls.Add(Me.SftwareMnuChkBx)
        Me.SoftwareInstallationsGroup.Controls.Add(Me.SSHChkBx)
        Me.SoftwareInstallationsGroup.Location = New System.Drawing.Point(12, 211)
        Me.SoftwareInstallationsGroup.Name = "SoftwareInstallationsGroup"
        Me.SoftwareInstallationsGroup.Size = New System.Drawing.Size(320, 85)
        Me.SoftwareInstallationsGroup.TabIndex = 6
        Me.SoftwareInstallationsGroup.TabStop = False
        Me.SoftwareInstallationsGroup.Text = "Software"
        '
        'Label2
        '
        Me.Label2.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label2.ForeColor = System.Drawing.Color.DodgerBlue
        Me.Label2.Location = New System.Drawing.Point(204, 64)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(110, 18)
        Me.Label2.TabIndex = 9
        Me.Label2.Text = "* = must be installed"
        '
        'LauncherChkBx
        '
        Me.LauncherChkBx.AutoSize = True
        Me.LauncherChkBx.Checked = True
        Me.LauncherChkBx.CheckState = System.Windows.Forms.CheckState.Checked
        Me.LauncherChkBx.Enabled = False
        Me.LauncherChkBx.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.LauncherChkBx.ForeColor = System.Drawing.Color.DodgerBlue
        Me.LauncherChkBx.Location = New System.Drawing.Point(201, 19)
        Me.LauncherChkBx.Name = "LauncherChkBx"
        Me.LauncherChkBx.Size = New System.Drawing.Size(106, 18)
        Me.LauncherChkBx.TabIndex = 7
        Me.LauncherChkBx.Text = "Install Launcher*"
        Me.LauncherChkBx.UseVisualStyleBackColor = True
        '
        'SftwareMnuChkBx
        '
        Me.SftwareMnuChkBx.AutoSize = True
        Me.SftwareMnuChkBx.Checked = True
        Me.SftwareMnuChkBx.CheckState = System.Windows.Forms.CheckState.Checked
        Me.SftwareMnuChkBx.Enabled = False
        Me.SftwareMnuChkBx.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.SftwareMnuChkBx.ForeColor = System.Drawing.Color.DodgerBlue
        Me.SftwareMnuChkBx.Location = New System.Drawing.Point(5, 52)
        Me.SftwareMnuChkBx.Name = "SftwareMnuChkBx"
        Me.SftwareMnuChkBx.Size = New System.Drawing.Size(135, 18)
        Me.SftwareMnuChkBx.TabIndex = 8
        Me.SftwareMnuChkBx.Text = "Install Software Menu*"
        Me.SftwareMnuChkBx.UseVisualStyleBackColor = True
        '
        'SSHChkBx
        '
        Me.SSHChkBx.AutoSize = True
        Me.SSHChkBx.Font = New System.Drawing.Font("Arial", 8.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.SSHChkBx.ForeColor = System.Drawing.Color.DodgerBlue
        Me.SSHChkBx.Location = New System.Drawing.Point(5, 19)
        Me.SSHChkBx.Name = "SSHChkBx"
        Me.SSHChkBx.Size = New System.Drawing.Size(77, 18)
        Me.SSHChkBx.TabIndex = 7
        Me.SSHChkBx.Text = "Install SSH"
        Me.SSHChkBx.UseVisualStyleBackColor = True
        '
        'CreatePatchStickBtn
        '
        Me.CreatePatchStickBtn.Location = New System.Drawing.Point(12, 315)
        Me.CreatePatchStickBtn.Name = "CreatePatchStickBtn"
        Me.CreatePatchStickBtn.Size = New System.Drawing.Size(133, 25)
        Me.CreatePatchStickBtn.TabIndex = 7
        Me.CreatePatchStickBtn.Text = "Create Patchstick"
        Me.CreatePatchStickBtn.UseVisualStyleBackColor = True
        '
        'FindCustomDmgDialog
        '
        Me.FindCustomDmgDialog.Filter = "Apple TV Firmware Files|*.dmg"
        '
        'SavePatchstickDialog
        '
        Me.SavePatchstickDialog.Filter = "Apple Patchstick Images | *.img"
        '
        'PatchStickForm
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.Color.White
        Me.ClientSize = New System.Drawing.Size(344, 351)
        Me.Controls.Add(Me.CreatePatchStickBtn)
        Me.Controls.Add(Me.SoftwareInstallationsGroup)
        Me.Controls.Add(Me.FirmwareGroup)
        Me.Controls.Add(Me.WelcomeLbl)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.AboutLnk)
        Me.MaximizeBox = False
        Me.Name = "PatchStickForm"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "Apple TV Patchstick Creator 2.0"
        Me.FirmwareGroup.ResumeLayout(False)
        Me.SoftwareInstallationsGroup.ResumeLayout(False)
        Me.SoftwareInstallationsGroup.PerformLayout()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents AboutLnk As System.Windows.Forms.LinkLabel
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents WelcomeLbl As System.Windows.Forms.Label
    Friend WithEvents FwVerLbl As System.Windows.Forms.Label
    Friend WithEvents FwBox As System.Windows.Forms.ComboBox
    Friend WithEvents FirmwareGroup As System.Windows.Forms.GroupBox
    Friend WithEvents SoftwareInstallationsGroup As System.Windows.Forms.GroupBox
    Friend WithEvents SSHChkBx As System.Windows.Forms.CheckBox
    Friend WithEvents SftwareMnuChkBx As System.Windows.Forms.CheckBox
    Friend WithEvents LauncherChkBx As System.Windows.Forms.CheckBox
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents CreatePatchStickBtn As System.Windows.Forms.Button
    Friend WithEvents CustomDMGBtn As System.Windows.Forms.Button
    Friend WithEvents FindCustomDmgDialog As System.Windows.Forms.OpenFileDialog
    Friend WithEvents SavePatchstickDialog As System.Windows.Forms.SaveFileDialog

End Class
