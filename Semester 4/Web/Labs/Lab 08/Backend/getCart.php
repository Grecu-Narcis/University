<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Headers: Content-Type");

require_once "config.php";

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    $sql_query = "SELECT * FROM product where id in
    (SELECT * from isInCart)";

    global $connection;
    $result = mysqli_query($connection, $sql_query);

    $products = array();

    while ($row = mysqli_fetch_assoc($result)) {
        $products[] = $row;
    }

    echo json_encode($products);
    mysqli_close($connection);
}