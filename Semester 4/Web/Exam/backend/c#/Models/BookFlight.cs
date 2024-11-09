namespace c_.Models
{
    public class BookFlight
    {
        public int id { get; set; }
        public string name { get; set; }

        public BookFlight(int id, string name)
        {
            this.id = id;
            this.name = name;
        }
    }
}
