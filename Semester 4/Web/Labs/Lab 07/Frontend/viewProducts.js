let currentPage = 1;

$('document').ready(function() {
    const searchParams = new URLSearchParams(window.location.search);
    // let category = searchParams.get('category');
    let category = localStorage.getItem('category');
    $('#previous').prop('disabled', true);
    //getAllProductsByCategory(category);
    getProductsByCategoryPage(category, currentPage);

    $('#next').click(function() {
        console.log('Next button clicked');
        // let page = searchParams.get('page');
        $('#previous').prop('disabled', false);

        currentPage += 1;
        getProductsByCategoryPage(category, currentPage);

        // window.location.href = 'viewProducts.html?page=' + page + '&category=' + category;
    });

    $('#previous').click(function() {
        console.log('Previous button clicked');
        let category = localStorage.getItem('category');

        //let page = searchParams.get('page');
        $('#next').prop('disabled', false);
        //page = parseInt(page) - 1;
        currentPage -= 1;
        getProductsByCategoryPage(category, currentPage);

        if (currentPage == 1) {
            $('#previous').prop('disabled', true);
        }
        //window.location.href = 'viewProducts.html?page=' + page + '&category=' + category;
    });
});

function getProductsByCategoryPage(category, page) {
    let productsInCart = [];

    $.ajax({
        url: 'http://localhost/Lab07/getProductsInCart.php',
        type: 'GET',
        async: false,
    })
    .then(function(response) {
        productsInCart = JSON.parse(response);
    });
    
    let currentPage = [];
    $.ajax({
        url: 'http://localhost/Lab07/getAllProductsByCategory.php?category=' + category+"&page="+page,
        type: 'GET'
    })
    .then((response) => {
        currentPage = JSON.parse(response);

        if (currentPage.length < 4) {
            $('#next').prop('disabled', true);
        }

        let productsTable = $('#products-body');
        productsTable.empty();

        currentPage.forEach(function(product) {
            let productRow = createProductRow(product, productsInCart);
            productsTable.append(productRow);
        });
    });
}

// function getAllProductsByCategory(requiredCategory) {
//     const searchParams = new URLSearchParams(window.location.search);
//     let page = searchParams.get('page');
//     let productsInCart = [];

//     $.ajax({
//         url: 'http://localhost/Lab07/getProductsInCart.php',
//         type: 'GET',
//         async: false,
//     })
//     .then(function(response) {
//         productsInCart = JSON.parse(response);
//         if (productsInCart.length < 4)
//             $('#next').prop('disabled', true);
//     });

//     $.ajax({
//         url: 'http://localhost/Lab07/getAllProductsByCategory.php?category=' + requiredCategory,
//         type: 'GET'
//     })
//     .then(function(response) {
//         let allProducts = JSON.parse(response);
//         allProducts = allProducts.slice((page - 1) * 4, page * 4);

//         if (allProducts.length < 4) {
//             $('#next').prop('disabled', true);
//         }

//         if (page == 1) {
//             $('#previous').prop('disabled', true);
//         }

//         let productsTable = $('#products-body');
//         productsTable.empty();

//         allProducts.forEach(function(product) {
//             let productRow = createProductRow(product, productsInCart);
//             productsTable.append(productRow);
//         });
//     },
//     function (error) {
//         console.error('Error', error);
//     });
// }


function createProductRow(product, productsInCart) {
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

    let editButton = $('<td></td>');
    let editButtonElement = $('<button></button>');
    editButtonElement.text('Edit');
    editButtonElement.click(function() {
        console.log('Edit button clicked');
        window.location.href = 'editProduct.html?id=' + product["id"];
    });

    editButton.append(editButtonElement);
    productRow.append(editButton);

    let addButton = $('<td></td>');
    let addButtonElement = $('<button type="button"></button>');
    addButtonElement.text('Add to cart');
    addButtonElement.click(function() {
        addButtonElement.prop('disabled', true);
        //window.location.href = 'addToCart.html?id=' + product["id"];
        $.ajax({
            url: 'http://localhost/Lab07/addToCart.php',
            type: 'POST',
            data: JSON.stringify({
                productID: product.id
            }),
        })
        .then((response) => {
            console.log('Product added to cart');
            console.log(response);
        },
        (error) => {
            console.error('Error', error);
        });
    });

    productsInCart.forEach((current) => {
        if (current.productID == product.id) {
            addButtonElement.prop('disabled', true);
        }
    })

    addButton.append(addButtonElement);
    productRow.append(addButton);

    return productRow;
}
