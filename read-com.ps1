function read-com {
$port= new-Object System.IO.Ports.SerialPort COM3,115200,None,8,one
$port.Open()
do{
$port.ReadLine()
}
while ($port.IsOpen)
}
read-com