<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: POST");
header("Access-Control-Allow-Headers: Content-Type");

require_once "config.php";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $requestBody = file_get_contents("php://input");
    $requestBodyObj = json_decode($requestBody, true);

    $productID = $requestBodyObj["productID"];

    $sql_command = "INSERT INTO isInCart (productID) VALUES ('$productID')";
    global $connection;

    mysqli_query($connection, $sql_command);

    echo json_encode($productID);
    mysqli_close($connection);
}
