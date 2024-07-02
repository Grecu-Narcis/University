<?php
header("Access-Control-Allow-Origin: *");
require_once "config.php";

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    global $connection;

    $productID = $_REQUEST['id'];
    $sql_query = "SELECT * FROM product where id='$productID'";
    $result = mysqli_query($connection, $sql_query);

    $user = $result->fetch_assoc();
    echo json_encode($user);
    mysqli_close($connection);
}