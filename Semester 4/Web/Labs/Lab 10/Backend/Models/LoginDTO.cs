namespace Backend.Models
{
    public class LoginDTO
    {
        public string Username { get; set; }
        public string Password { get; set; }

        public LoginDTO(string username, string password)
        {
            this.Username = username;
            this.Password = password;
        }
    }
}
