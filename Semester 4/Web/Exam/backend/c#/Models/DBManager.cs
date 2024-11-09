using c_.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Data.SqlClient;
using Microsoft.IdentityModel.Tokens;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace Backend.Models
{
    public class DBManager
    {
        private readonly string connectionString;

        public DBManager(IConfiguration configuration)
        {
            this.connectionString = configuration.GetConnectionString("DefaultConnection");
        }

        //public bool Login(request)
        //{
        //    using (var connection = new SqlConnection(connectionString))
        //    {
        //        connection.Open();

        //        using (var command = new SqlCommand("SELECT * FROM users where name=@name", connection))
        //        {
        //            command.Parameters.Add(new SqlParameter("@name", name));

        //            using (var reader = command.ExecuteReader())
        //            {
        //                while (reader.Read())
        //                {
        //                    var username = reader.GetString(0);
        //                    var password = reader.GetString(1);


        //                }
        //            }
        //        }
        //    }

        //    return false;
        //}

        public List<Flight> GetFlights(string date, string city)
        {
            Console.WriteLine(date);
            Console.WriteLine(city);
            var result = new List<Flight>();

            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("SELECT * from Flights where date=@date and destinationCity=@city and availableSeats > 0", connection))
                {
                    command.Parameters.Add(new SqlParameter("@date", date));
                    command.Parameters.Add(new SqlParameter("@city", city));

                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            result.Add(new Flight(reader.GetInt32(0), reader.GetString(1), reader.GetString(2), reader.GetInt32(3)));
                        }
                    }
                }
            }

            return result;
        }

        public List<Hotel> GetHotels(string date, string city)
        {
            var result = new List<Hotel>();

            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("SELECT * from Hotels where date=@date and city=@city and availableRooms > 0", connection))
                {
                    command.Parameters.Add(new SqlParameter("@date", date));
                    command.Parameters.Add(new SqlParameter("@city", city));

                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            result.Add(new Hotel(reader.GetInt32(0), reader.GetString(1), reader.GetString(3), reader.GetString(2), reader.GetInt32(4)));
                        }
                    }
                }
            }

            return result;
        }

        public int BookFlight(BookFlight flight)
        {
            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("update flights set availableSeats = availableSeats - 1 where flightId=@id", connection))
                {
                    command.Parameters.Add(new SqlParameter("@id", flight.id));

                    command.ExecuteNonQuery();
                }

                using (var command = new SqlCommand("insert into Reservations values (@name, '', 'Flight', @id);", connection))
                {
                    command.Parameters.Add(new SqlParameter("@id", flight.id));
                    command.Parameters.Add(new SqlParameter("@name", flight.name));

                    command.ExecuteNonQuery();
                }

                using (var command = new SqlCommand("select id from Reservations order by id desc;", connection))
                {
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            return reader.GetInt32(0);
                        }
                    }
                }
            }

            return -1;
        }

        public int BookHotel(BookHotel hotel)
        {
            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("update hotels set availableRooms = availableRooms - 1 where hotelId=@id", connection))
                {
                    command.Parameters.Add(new SqlParameter("@id", hotel.id));

                    command.ExecuteNonQuery();
                }

                using (var command = new SqlCommand("insert into Reservations values (@name, '', 'Hotel', @id);", connection))
                {
                    command.Parameters.Add(new SqlParameter("@id", hotel.id));
                    command.Parameters.Add(new SqlParameter("@name", hotel.name));

                    command.ExecuteNonQuery();
                }

                using (var command = new SqlCommand("select id from Reservations order by id desc;", connection))
                {
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            return reader.GetInt32(0);
                        }
                    }
                }
            }

            return -1;
        }

        public void CancelReservations(List<int> reservations)
        {
            for (var i = 0; i < reservations.Count; i++)
                CancelReservation(reservations[i]);
        }

        public void CancelReservation(int id)
        {
            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                string type = "";
                int resId = -1;

                using (var command = new SqlCommand("select type, idReservedResource from Reservations where id=@id", connection))
                {
                    command.Parameters.Add(new SqlParameter("@id", id));

                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            type = reader.GetString(0);
                            resId = reader.GetInt32(1);
                        }
                    }
                }

                if (type == "Hotel")
                {
                    Console.WriteLine(resId);
                    using (var command = new SqlCommand("update hotels set availableRooms = availableRooms + 1 where hotelId=@id", connection))
                    {
                        command.Parameters.Add(new SqlParameter("@id", resId));

                        command.ExecuteNonQuery();
                    }
                }

                else
                {
                    using (var command = new SqlCommand("update flights set availableSeats = availableSeats + 1 where flightId=@id", connection))
                    {
                        command.Parameters.Add(new SqlParameter("@id", resId));

                        command.ExecuteNonQuery();
                    }
                }

                using (var command = new SqlCommand("delete from reservations where id=@id", connection))
                {
                    command.Parameters.Add(new SqlParameter("@id", id));

                    command.ExecuteNonQuery();
                }
            }
        }
    } 
}
