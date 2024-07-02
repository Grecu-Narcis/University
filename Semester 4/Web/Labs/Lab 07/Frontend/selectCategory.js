$('document').ready(function() {
    console.log('Document is ready');
    getAllCategories();

    $('#submit').click(function() {
        let requiredCategory = $('#categories').val();
        window.location.href = 'viewProducts.html';

        localStorage.setItem('category', requiredCategory);
    });
});

function getAllCategories() {
    console.log('Getting all categories');
    $.ajax({
        url: 'http://localhost/Lab07/getCategories.php',
        type: 'GET'
    })
    .then(function(response) {
        let categories = JSON.parse(response);
        let categoriesList = $('#categories');

        categoriesList.empty();

        categories.forEach(function(category) {
            let categoryElement = $('<option></option>');
            console.log(category);
            categoryElement.text(category["category"]);
            categoryElement.val(category["category"]);

            categoriesList.append(categoryElement);
        });
    },
    function(error) {
        console.error('Error', error);
    });
}