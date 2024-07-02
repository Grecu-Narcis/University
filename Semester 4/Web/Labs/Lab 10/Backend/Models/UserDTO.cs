namespace Backend.Models
{
    public class UserDTO
    {
        public int userId { get; set; }

        public UserDTO(int userId)
        {
            this.userId = userId;
        }
    }
}
