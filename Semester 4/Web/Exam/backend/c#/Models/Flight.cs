namespace c_.Models
{
    public class Flight
    {
        public int id { get; set; }
        public string date { get; set; }
        public string destination { get; set; }
        public int seats { get; set; }

        public Flight(int id, string date, string destination, int seats)
        {
            this.id = id;
            this.date = date;
            this.destination = destination;
            this.seats = seats;
        }
    }
}
