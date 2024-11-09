$('document').ready(function() {
    getItems();

    $("#cancel").click(() => cancel());
});

function getItems() {
    let items = [];

    let city = localStorage.getItem("city");
    let date = localStorage.getItem("date");

    $.ajax({
        url: 'http://localhost:5294/api/getHotels/' + date + "/" + city,
        type: 'GET',
        headers: {
            'Content-type':'application/json; charset=UTF-8',
          }
    })
    .then(function(response) {
        items = response;
        console.log(items);

        let itemsTable = $("#items-body");
       
        itemsTable.empty();
        
        items.forEach(document => {
            let row = createItemRow(document);
            console.log(row);

            itemsTable.append(row);
        });
    });
}

function createItemRow(item) {
    let documentRow = $('<tr></tr>');

    let documentName = $('<td></td>');
    documentName.text(item.date);
    documentRow.append(documentName);

    let keyword1 = $('<td></td>');
    keyword1.text(item.city);
    documentRow.append(keyword1);

    let keyword2 = $('<td></td>');
    keyword2.text(item.rooms);
    documentRow.append(keyword2);

    let editButton = $('<td></td>');
    let editButtonElement = $('<button></button>');
    editButtonElement.text('Book');
    editButtonElement.click(function() {
        bookHotel(item.id);
        alert("booked successfully");
    });

    editButton.append(editButtonElement);
    documentRow.append(editButton);

    return documentRow;
}

function bookHotel(hotelId) {
    let name = localStorage.getItem('name');

    $.ajax({
        url: 'http://localhost:5294/api/bookHotel',
        type: 'POST',
        async: false,
        data: JSON.stringify({
            id: hotelId,
            name: name,
        }),
        headers: { 
            'Accept': 'application/json',
            'Content-Type': 'application/json' 
        },
    })
    .then((response) => {
        console.log(response);
        let reservations = [];
        if (localStorage.getItem('reservations') == null)
        {
            reservations.push(response);
            localStorage.setItem('reservations', JSON.stringify(reservations));
        }

        else {
            reservations = JSON.parse(localStorage.getItem('reservations'));
            reservations.push(response);

            localStorage.setItem('reservations', JSON.stringify(reservations));
        }


        getItems()
    }); 
}

function cancel() {
    let reservations = JSON.parse(localStorage.getItem('reservations'));

    if (reservations == null) return;

    reservations.forEach(reservation => {
    $.ajax({
        url: 'http://localhost:5294/api/cancel',
        type: 'POST',
        async: false,
        data: JSON.stringify(
            {
                "id": reservation
            }
        ),
        headers: { 
            'Accept': 'application/json',
            'Content-Type': 'application/json' 
        },
    });
});

    localStorage.removeItem('reservations');
    getItems();
}