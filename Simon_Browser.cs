Public Class Form1
    Private Sub Timer1_Tick_1(sender As Object, e As EventArgs) Handles Timer1.Tick
        If (SerialPort1.IsOpen <> True) Then
            SerialPort1.Open()
        End If
        If (SerialPort1.BytesToRead > 0) Then
            Dim ARDUINO As String
            ARDUINO = Convert.ToChar(SerialPort1.ReadByte()).ToString()
            If (ARDUINO.Equals("")) Then
                Return
            ElseIf (ARDUINO.Equals("R")) Then
                Dim REDButton As HtmlElement = WebBrowser1.Document.GetElementById("PRESSR")
                REDButton.InvokeMember("click")
            ElseIf (ARDUINO.Equals("G")) Then
                Dim GREENButton As HtmlElement = WebBrowser1.Document.GetElementById("PRESSG")
                GREENButton.InvokeMember("click")
            ElseIf (ARDUINO.Equals("B")) Then
                Dim BLUEButton As HtmlElement = WebBrowser1.Document.GetElementById("PRESSB")
                BLUEButton.InvokeMember("click")
            ElseIf (ARDUINO.Equals("Y")) Then
                Dim YELLOWButton As HtmlElement = WebBrowser1.Document.GetElementById("PRESSY")
                YELLOWButton.InvokeMember("click")
            ElseIf (ARDUINO.Equals("S")) Then
                Dim STARTButton As HtmlElement = WebBrowser1.Document.GetElementById("button1")
                STARTButton.InvokeMember("click")
            End If
        End If
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        WebBrowser1.Navigate(TextBox1.Text)
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Me.Text = "Web Browser"
    End Sub
End Class
