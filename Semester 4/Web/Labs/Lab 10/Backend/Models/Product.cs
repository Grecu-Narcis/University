namespace Backend.Models
{
    public class Product
    {
        public int ProductId { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public decimal Price { get; set; }
        public string Category { get; set; }

        public Product(int productId, string name, decimal price, string description, string category)
        {
            ProductId=productId;
            Name=name;
            Description=description;
            Price=price;
            Category=category;
        }
    }
}
