namespace Backend.Models
{
    public class CartProductDTO
    {
        public int productID { get; set; }

        public CartProductDTO(int productId)
        {
            this.productID = productId;
        }
    }
}
