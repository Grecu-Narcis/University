using Backend.Models;
using Microsoft.Data.SqlClient;

namespace Backend.Repository
{
    public class LoginRepository
    {
        private readonly string connectionString;

        public LoginRepository(IConfiguration configuration)
        {
            this.connectionString = configuration.GetConnectionString("DefaultConnection");
        }

        public UserDTO FindUserByUsernameAndPassword(string username, string password)
        {
            UserDTO user = new UserDTO(-1);

            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("SELECT * from Users where username=@username and password=@password", connection))
                {
                    command.Parameters.Add(new SqlParameter("username", username));
                    command.Parameters.Add(new SqlParameter("password", password));

                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            user.userId = reader.GetInt32(0);
                        }
                    }
                }
            }

            return user;
        }
    }
}
