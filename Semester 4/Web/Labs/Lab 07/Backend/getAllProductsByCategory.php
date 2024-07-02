<?php
header("Access-Control-Allow-Origin: *");
require_once "config.php";

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    $required_category = $_REQUEST['category'];
    $required_page = $_REQUEST['page'];
    $count_query = "SELECT * FROM product WHERE category = '$required_category'";
    global $connection;

    $result = mysqli_query($connection, $count_query);

    if ($result) {
        $products = array();

        while ($row = $result->fetch_assoc()) {
            $products[] = $row;
        }

        $products_list = array_slice($products, ($required_page - 1) * 5, 5);

        echo json_encode(array('products' => $products_list, 'total' => count($products)));
        mysqli_close($connection);
    }
}