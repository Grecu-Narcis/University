using Backend.Models;
using c_.Models;
using Microsoft.AspNetCore.Mvc;

namespace Backend.Controllers
{
    [Route("api")]
    [ApiController]
    public class ApiController : Controller
    {
        public DBManager dbManager;

        public ApiController(DBManager manager)
        {
            this.dbManager = manager;
        }

        //[HttpPost("login")]
        //public bool Login(request)
        //{

        //}


        [HttpGet("getFlights/{date}/{city}")]
        public List<Flight> GetFlights(string date, string city)
        {
            return dbManager.GetFlights(date, city);
        }

        [HttpGet("getHotels/{date}/{city}")]
        public List<Hotel> GetHotels(string date, string city)
        {
            return dbManager.GetHotels(date, city);
        }

        [HttpPost("bookFlight")]
        public int BookFlight([FromBody] BookFlight flightDto)
        {
            return this.dbManager.BookFlight(flightDto);
        }

        [HttpPost("bookHotel")]
        public int BookHotel([FromBody] BookHotel flightDto)
        {
            return this.dbManager.BookHotel(flightDto);
        }

        [HttpPost("cancel")]
        public void Cancel([FromBody] Cancel id)
        {
            dbManager.CancelReservation(id.id);
        }

        [HttpGet]
        public IActionResult Index()
        {
            return View();
        }
    }
}
