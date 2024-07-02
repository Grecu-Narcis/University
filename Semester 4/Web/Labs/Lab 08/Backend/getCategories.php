<?php
header("Access-Control-Allow-Origin: *");
require_once "config.php";

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    $sql_query = "SELECT DISTINCT category FROM product";
    global $connection;

    $result = mysqli_query($connection, $sql_query);

    if ($result) {
        $categories = array();

        while ($row = $result->fetch_assoc()) {
            $categories[] = $row;
        }

        echo json_encode($categories);
        mysqli_close($connection);
    }
}