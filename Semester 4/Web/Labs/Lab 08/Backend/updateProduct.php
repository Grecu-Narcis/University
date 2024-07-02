<?php
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: PUT");
header("Access-Control-Allow-Headers: Content-Type");

require_once "config.php";

global $connection;

if ($_SERVER['REQUEST_METHOD'] == 'PUT') {
    $requestBody = file_get_contents('php://input');
    $requestObj = json_decode($requestBody, true);

    $productID = mysqli_real_escape_string($connection, $requestObj['id']);
    $productName = mysqli_real_escape_string($connection, $requestObj['name']);
    $productPrice = mysqli_real_escape_string($connection, $requestObj['price']);
    $productCategory = mysqli_real_escape_string($connection, $requestObj['category']);
    $productDescription = mysqli_real_escape_string($connection, $requestObj['description']);

    if (!is_numeric($productID))
        echo json_encode(array('error' => 'product id must be a number!'));

    if (!is_numeric($productPrice))
        echo json_encode(array('error' => 'product price must be a number!'));

    if (strlen($productName) < 3)
        echo json_encode(array('error' => 'product name must have length at least 3'));

    if (!strlen($productDescription) < 3)
        echo json_encode(array('error' => 'product description must have length at least 3'));

    if (!strlen($productCategory) < 3)
        echo json_encode(array('error' => 'product category must have length at least 3'));

    $count_query = "UPDATE product set name='$productName', price='$productPrice',
     category='$productCategory', description='$productDescription' where id='$productID'";

    $result = mysqli_query($connection, $count_query);
    echo json_encode($result);
}