using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace Lab4
{
    internal class AsyncAwaitSolution
    {
        private List<string> urls;
        private int BufferSize = 1024;

        public AsyncAwaitSolution(List<string> urls)
        {
            this.urls = urls;
        }

        public void Run()
        {
            Console.WriteLine("Async-await");

            var tasks = this.urls.Select(url => Task.Run(() => HandleUrl(url))).ToList();

            Task.WhenAll(tasks).Wait();
        }

        private async Task HandleUrl(string url)
        {
            Console.WriteLine("Begin connect");

            var index = url.IndexOf('/');
            var baseUrl = index < 0 ? url : url[..index];
            var urlPath = index < 0 ? "/" : url[index..];

            var ipAddress = Dns.GetHostEntry(baseUrl).AddressList[0];

            var endPoint = new IPEndPoint(IPAddress.Loopback, 3000);

            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            await ConnectSocket(socket, endPoint);
            await SendRequest(socket, urlPath, baseUrl);
            await ReceiveResponse(socket);
        }

        private Task<Socket> ConnectSocket(Socket socket, EndPoint endpoint)
        {
            var promise = new TaskCompletionSource<Socket>();

            socket.BeginConnect(endpoint, result =>
            {
                socket.EndConnect(result);
                promise.SetResult(socket);
            }, null);

            return promise.Task;
        }

        private Task<Socket> SendRequest(Socket socket, string urlPath, string baseUrl)
        {
            Console.WriteLine("Begin send!");


            var promise = new TaskCompletionSource<Socket>();

            var stringToSend = $"GET {urlPath} HTTP/1.1\r\n" +
                $"Host: {baseUrl}\r\n" +
                "Content-Length: 0\r\n\r\n";

            var encodedString = Encoding.ASCII.GetBytes(stringToSend);

            socket.BeginSend(encodedString, 0, encodedString.Length, SocketFlags.None, result =>
            {
                socket.EndSend(result);
                promise.SetResult(socket);
            }, null);

            return promise.Task;
        }

        private Task<Socket> ReceiveResponse(Socket socket)
        {
            Console.WriteLine("Begin Receive!");

            var promise = new TaskCompletionSource<Socket>();

            var buffer = new byte[BufferSize];

            socket.BeginReceive(buffer, 0, BufferSize, SocketFlags.None, result =>
            {
                var bytesReceived = socket.EndReceive(result);
                HandleReceive(socket, buffer, bytesReceived);
                promise.SetResult(socket);
            }, null);

            return promise.Task;
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
