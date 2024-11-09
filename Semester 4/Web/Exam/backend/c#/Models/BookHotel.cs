namespace c_.Models
{
    public class BookHotel
    {
        public int id { get; set; }
        public string name { get; set; }

        public BookHotel(int id, string name)
        {
            this.id = id;
            this.name = name;
        }
    }
}
