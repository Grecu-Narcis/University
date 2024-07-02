package ubb.backend.models;

import java.sql.*;

public class DBManager {
    private static final String URL = "jdbc:mysql://localhost:3306/lab9web";
    private static final String USER = "root";
    private static final String PASSWORD = "cocos123";

    public static User getUserByUsername(String username) {
        User requiredUser = null;

        String statement = "Select * from users where username=?";

        try {
            Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
            PreparedStatement preparedStatement = connection.prepareStatement(statement);
            preparedStatement.setString(1, username);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                requiredUser = new User(resultSet.getInt("userId"),
                    resultSet.getString("username"),
                    resultSet.getString("password"),
                    resultSet.getInt("timeSpent"));
            }
        }

        catch (SQLException e) {
            e.printStackTrace();
        }

        return requiredUser;
    }

    public static User getUserById(int userId) {
        User requiredUser = null;

        String statement = "Select * from users where userId=?";

        try {
            Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
            PreparedStatement preparedStatement = connection.prepareStatement(statement);
            preparedStatement.setInt(1, userId);
            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                requiredUser = new User(resultSet.getInt("userId"),
                    resultSet.getString("username"),
                    resultSet.getString("password"),
                    resultSet.getInt("timeSpent"));
            }
        }

        catch (SQLException e) {
            e.printStackTrace();
        }

        return requiredUser;
    }

    public static void addMove(String moveDirection, int userId) {
        try {
            String statement = "insert into Moves(moveDirection, userId) values(?, ?)";
            Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
            PreparedStatement preparedStatement = connection.prepareStatement(statement);
            preparedStatement.setString(1, moveDirection);
            preparedStatement.setInt(2, userId);

            preparedStatement.execute();
        }
        catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void updateTimeSpent(int userId, int newTime) {
        try {
            String statement = "update Users set timeSpent = timeSpent + ? where userId = ?;";
            Connection connection = DriverManager.getConnection(URL, USER, PASSWORD);
            PreparedStatement preparedStatement = connection.prepareStatement(statement);

            preparedStatement.setInt(1, newTime);
            preparedStatement.setInt(2, userId);

            preparedStatement.execute();
        }
        catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}
