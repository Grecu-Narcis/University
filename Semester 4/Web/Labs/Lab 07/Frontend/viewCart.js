$('document').ready(() => {
    loadProductsInCart();

    $("#no").click(() => {
        $("#modal").css("display", "none");
    })
});

function loadProductsInCart() {
    $.ajax({
        url: 'http://localhost/Lab07/getCart.php',
        type: 'GET',
    })
    .then((response) => {
        console.log(response);
        let productsInCart = JSON.parse(response);
        let productsTable = $('#products-body');
        productsTable.empty();

        productsInCart.forEach((product) => {
            let productRow = createProductRow(product);
            productsTable.append(productRow);
        });
    },
    (error) => {
        console.error('Error', error);
    });
}

function createProductRow(product) {
    console.log("hey");
    let productRow = $('<tr></tr>');

    let productName = $('<td></td>');
    productName.text(product.name);
    productRow.append(productName);

    let productDescription = $('<td></td>');
    productDescription.text(product.description);
    productRow.append(productDescription);

    let productPrice = $('<td></td>');
    productPrice.text(product.price);
    productRow.append(productPrice);

    let productCategory = $('<td></td>');
    productCategory.text(product.category);
    productRow.append(productCategory);

    let deleteButton = $('<button></button>');
    deleteButton.text('Delete');
    deleteButton.click(() => {
        $("#modal").css("display", "block");
        $("#yes").click(() => {
            deleteProductFromCart(product.id);
            $("#modal").css("display", "none");
        });
    });

    let deleteButtonElement = $('<td></td>');
    deleteButtonElement.append(deleteButton);

    productRow.append(deleteButtonElement);

    return productRow;
}

function deleteProductFromCart(productId) {
    $.ajax({
        url: 'http://localhost/Lab07/deleteFromCart.php',
        type: 'DELETE',
        data: JSON.stringify({
            id: productId
        })
    })
    .then(() => {
        loadProductsInCart();
    });
}