package ubb.backend.models;

public class User {
    public int userId;
    public String username;
    public String password;
    public int timeSpent;

    public User(int userId, String username, String password, int timeSpent) {
        this.userId = userId;
        this.username = username;
        this.password = password;
        this.timeSpent = timeSpent;
    }
}
