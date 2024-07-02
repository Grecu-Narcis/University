namespace Backend.Models
{
    public class AddToCartDTO
    {
        public int productID { get; set; }

        public AddToCartDTO(int productId)
        {
            this.productID = productId;
        }
    }
}
