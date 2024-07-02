$(document).ready(() => {
    const searchParams = new URLSearchParams(window.location.search);
    let id = searchParams.get('id');
    getProductDetails(id);

    $('#submit').click(() => {
        let name = $('#name').val();
        let price = $('#price').val();
        let category = $('#category').val();
        let description = $('#description').val();

        if (!name || !price || !category || !description) {
            alert('Please fill all fields');
            window.location.href = 'editProduct.html?id=' + id;
            return;
        }

        if (name.length < 3) {
            alert('Name should be at least 3 characters long');
            window.location.href = 'editProduct.html?id=' + id;
            return;
        }

        if (category.length < 3) {
            alert('Category should be at least 3 characters long');
            window.location.href = 'editProduct.html?id=' + id;
            return;
        }

        if (description.length < 3) {
            alert('Description should be at least 3 characters long');
            window.location.href = 'editProduct.html?id=' + id;
            return;
        }

        if (price < 0) {
            alert('Price should be a positive number');
            window.location.href = 'editProduct.html?id=' + id;
            return;
        }

        let product = {
            id: id,
            name: name,
            price: price,
            category: category,
            description: description
        };

        $.ajax({
            url: 'http://localhost/Lab07/updateProduct.php',
            type: 'PUT',
            data: JSON.stringify(product)
        })
        .then((response) => {
            console.log('Product updated successfully');
            window.location.href = 'index.html';
        });
    });
});

function getProductDetails(id) {
    $.ajax({
        url: 'http://localhost/Lab07/getProductDetails.php?id=' + id,
        type: 'GET'
    })
    .then((response) => {
        let product = JSON.parse(response);
        $('#name').val(product.name);
        $('#price').val(product.price);
        $('#category').val(product.category);
        $('#description').val(product.description);
    });
}