using Backend.Models;
using Microsoft.Data.SqlClient;

namespace Backend.Repository
{
    public class ProductRepository
    {
        private readonly string connectionString;

        public ProductRepository(IConfiguration configuration)
        {
            this.connectionString = configuration.GetConnectionString("DefaultConnection");
        }

        public List<string> GetAllCategories()
        {
            var categories = new List<string>();

            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("SELECT DISTINCT category from Products", connection))
                {
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            categories.Add(reader.GetString(0));
                        }
                    }
                }
            }

            return categories;
        }

        public List<Product> GetAllProductsByCategory(string category, int page)
        {
            var products = new List<Product>();

            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("SELECT * from Products where category = @category order by id offset @OffsetRows ROWS FETCH NEXT @FetchRows ROWS ONLY", connection))
                {
                    command.Parameters.Add(new SqlParameter("@category", category));
                    command.Parameters.Add(new SqlParameter("@OffsetRows", (page - 1) * 5));
                    command.Parameters.Add(new SqlParameter("@FetchRows", 5));
                        
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            products.Add(new Product(
                                reader.GetInt32(0),
                                reader.GetString(1),
                                reader.GetDecimal(2),
                                reader.GetString(3),
                                reader.GetString(4)));
                        }
                    }
                }
            }

            return products;
        }

        public int GetProductsCountByCategory(string category)
        {
            int result = 0;

            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("SELECT count(*) from Products where category = @category", connection))
                {
                    command.Parameters.Add(new SqlParameter("@category", category));

                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            result = reader.GetInt32(0);
                        }
                    }
                }
            }

            return result;
        }

        public List<CartProductDTO> GetProductsInCart()
        {
            var result = new List<CartProductDTO>();

            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("SELECT productId from isInCart", connection))
                {
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            result.Add(new CartProductDTO(reader.GetInt32(0)));
                        }
                    }
                }
            }

            return result;
        }

        public void AddToCart(int productId)
        {
            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("INSERT INTO isInCart(productId) values (@productId)", connection))
                {
                    command.Parameters.Add(new SqlParameter("@productId", productId));

                    command.ExecuteNonQuery();
                }
            }
        }

        public Product GetById(int productId)
        {
            Product result = null;

            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("SELECT * FROM Products WHERE id=@productId", connection))
                {
                    command.Parameters.Add(new SqlParameter("@productId", productId));

                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            result = new Product(
                                reader.GetInt32(0),
                                reader.GetString(1),
                                reader.GetDecimal(2),
                                reader.GetString(3),
                                reader.GetString(4)
                                );
                        }
                    }
                }
            }

            return result;
        }

        public void UpdateProduct(Product product)
        {
            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("UPDATE Products SET name=@name, price=@price, description=@description, category=@category WHERE id=@productId", connection))
                {
                    command.Parameters.Add(new SqlParameter("@name", product.Name));
                    command.Parameters.Add(new SqlParameter("@price", product.Price));
                    command.Parameters.Add(new SqlParameter("@description", product.Description));
                    command.Parameters.Add(new SqlParameter("@category", product.Category));
                    command.Parameters.Add(new SqlParameter("@productId", product.ProductId));

                    command.ExecuteNonQuery();
                }
            }
        }

        public List<Product> GetCart()
        {
            var result = new List<Product>();

            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("SELECT * FROM Products where id in (SELECT * FROM isInCart)", connection))
                {
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            result.Add(new Product(
                                reader.GetInt32(0),
                                reader.GetString(1),
                                reader.GetDecimal(2),
                                reader.GetString(3),
                                reader.GetString(4)));
                        }
                    }
                }
            }

            return result;
        }

        public void RemoveFromCart(int productId)
        {
            using (var connection = new SqlConnection(connectionString))
            {
                connection.Open();

                using (var command = new SqlCommand("DELETE FROM isInCart where productId=@productId", connection))
                {
                    command.Parameters.Add(new SqlParameter("@productId", productId));

                    command.ExecuteNonQuery();
                }
            }
        }
    }
}
