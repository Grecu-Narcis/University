<?php
header("Access-Control-Allow-Origin: *");
require_once "config.php";

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    $sql_query = "SELECT * FROM isInCart";
    global $connection;

    $result = mysqli_query($connection, $sql_query);

    if ($result) {
        $products = array();

        while ($row = $result->fetch_assoc()) {
            $products[] = $row;
        }

        echo json_encode($products);
        mysqli_close($connection);
    }
}