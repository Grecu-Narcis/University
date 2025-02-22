using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Lab4
{
    internal class CallBackSolution
    {
        private List<string> urls;
        private int BufferSize = 1024;

        public CallBackSolution(List<string> urls)
        {
            this.urls = urls;
        }

        public void Run()
        {
            Console.WriteLine("Callback");
            this.urls.ForEach(url => HandleUrl(url));
        }

        private void HandleUrl(string url)
        {
            Console.WriteLine("Begin connect");
            var index = url.IndexOf('/');
            var baseUrl = index < 0 ? url : url[..index];
            var urlPath = index < 0 ? "/" : url[index..];

            var ipAddress = Dns.GetHostEntry(baseUrl).AddressList[0];

            var endPoint = new IPEndPoint(ipAddress, 80);

            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            socket.BeginConnect(endPoint, result => {     
                socket.EndConnect(result);
              
                HandleConnectionSuccess(socket, urlPath, baseUrl);
                }, null);

            do
            {
                Thread.Sleep(100);
            }
            while (socket.Connected);
        }

        private void HandleConnectionSuccess(Socket socket, string urlPath, string baseUrl)
        {
            Console.WriteLine("Begin send!");

            var stringToSend = $"GET {urlPath} HTTP/1.1\r\n" +
                $"Host: {baseUrl}\r\n" +
                "Content-Length: 0\r\n\r\n";

            var encodedString = Encoding.ASCII.GetBytes(stringToSend);

            socket.BeginSend(encodedString, 0, encodedString.Length, SocketFlags.None, result =>
            {
                var sentBytesCount = socket.EndSend(result);

                HandleSent(socket);
            }, null);
        }

        private void HandleSent(Socket socket)
        {
            Console.WriteLine("Begin Receive!");
            var buffer = new byte[BufferSize];

            socket.BeginReceive(buffer, 0, BufferSize, SocketFlags.None, result =>
            {
                var bytesReceived = socket.EndReceive(result);
                HandleReceive(socket, buffer, bytesReceived);
            }, null);
        }

        private void HandleReceive(Socket socket, byte[] buffer, int bytesReceived)
        {
            var responseText = Encoding.UTF8.GetString(buffer, 0, bytesReceived);

            var contentLengthHeader = responseText.Split('\n')
                .Where(line => line.StartsWith("Content-Length"))
                .First();

            Console.WriteLine(contentLengthHeader);

            socket.Close();
        }
    }
}
