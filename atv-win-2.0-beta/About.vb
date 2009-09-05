Public Class About

    Private Sub About_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        FormFade("out")
    End Sub

    Private Sub About_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        FormFade("in")
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
End Class