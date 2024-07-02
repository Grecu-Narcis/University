<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: DELETE");
header("Access-Control-Allow-Headers: Content-Type");

require_once "config.php";

if ($_SERVER['REQUEST_METHOD'] == 'DELETE') {
    $requestBody = file_get_contents("php://input");
    $requestBodyObj = json_decode($requestBody, true);

    $productID = $requestBodyObj["id"];

    if (!is_numeric($productID))
        echo json_encode(array("error" => "product id must be number"));

    $sql_command = "DELETE FROM isInCart WHERE productID='$productID'";
    global $connection;

    mysqli_query($connection, $sql_command);

    echo json_encode($productID);
    mysqli_close($connection);
}