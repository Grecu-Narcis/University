namespace Backend.Models
{
    public class ProductsDTO
    {
        public List<Product> products { get; set; }
        public int total { get; set; }

        public ProductsDTO(List<Product> products, int total)
        {
            this.products = products;
            this.total = total;
        }
    }
}
