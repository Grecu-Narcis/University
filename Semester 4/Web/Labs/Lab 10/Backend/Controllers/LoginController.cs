using Backend.Models;
using Backend.Repository;
using Microsoft.AspNetCore.Mvc;

namespace Backend.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class LoginController : Controller
    {
        private LoginRepository loginRepository;

        public LoginController(LoginRepository loginRepository)
        {
            this.loginRepository = loginRepository;
        }

        [HttpPost("login")]
        public ActionResult<UserDTO> Login([FromBody] LoginDTO loginDTO)
        {
            UserDTO userDTO = this.loginRepository.FindUserByUsernameAndPassword(loginDTO.Username, loginDTO.Password);

            if (userDTO.userId == -1) return BadRequest("Invalid credentials!");
            return Ok(userDTO);
        }

        [HttpGet]
        public IActionResult Index()
        {
            return View();
        }
    }
}
