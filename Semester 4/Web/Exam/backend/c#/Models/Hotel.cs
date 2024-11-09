namespace c_.Models
{
    public class Hotel
    {
        public int id { get; set; }
        public string name { get; set; }
        public string date { get; set; }
        public string city { get; set; }
        public int rooms { get; set; }

        public Hotel(int id, string name, string city, string date, int rooms)
        {
            this.id = id;
            this.name = name;
            this.rooms = rooms;
            this.date = date;
            this.city = city;
        }
    }
}
