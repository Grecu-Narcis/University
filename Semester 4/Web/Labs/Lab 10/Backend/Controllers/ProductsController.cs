using Backend.Models;
using Backend.Repository;
using Microsoft.AspNetCore.Mvc;

namespace Backend.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ProductsController : Controller
    {
        private ProductRepository productRepository;

        public ProductsController(ProductRepository productRepository)
        {
            this.productRepository = productRepository;
        }

        [HttpGet("getCategories")]
        public ActionResult<List<string>> GetAllCategories()
        {
            return this.productRepository.GetAllCategories();
        }

        [HttpGet("getAllProductsByCategory/{category}/{page}")]
        public ActionResult<ProductsDTO> GetAllProductsByCategory([FromRoute] string category, [FromRoute] int page)
        {
            var products = this.productRepository.GetAllProductsByCategory(category, page);
            var total = this.productRepository.GetProductsCountByCategory(category);

            return new ProductsDTO(products, total);
        }

        [HttpGet("getProductsInCart")]
        public ActionResult<List<CartProductDTO>> GetProductsInCart()
        {
            return this.productRepository.GetProductsInCart();
        }

        [HttpPost("addToCart")]
        public void AddToCart([FromBody] AddToCartDTO addToCartDTO)
        {
            this.productRepository.AddToCart(addToCartDTO.productID);
        }

        [HttpGet("getProductsDetails/{productId}")]
        public ActionResult<Product> GetProductDetails([FromRoute] int productId)
        {
            return this.productRepository.GetById(productId);
        }

        [HttpPut("updateProduct")]
        public void UpdateProduct([FromBody] Product product)
        {
            this.productRepository.UpdateProduct(product);
        }

        [HttpGet("getCart")]
        public ActionResult<List<Product>> GetCart()
        {
            return this.productRepository.GetCart();
        }

        [HttpDelete("removeFromCart/{productId}")]
        public void RemoveFromCart([FromRoute] int productId)
        {
            this.productRepository.RemoveFromCart(productId);
        }

        [HttpGet]
        public IActionResult Index()
        {
            return View();
        }
    }
}
