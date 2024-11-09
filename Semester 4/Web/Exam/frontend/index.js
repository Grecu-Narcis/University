$(document).ready(() => {
    $("#submit").click(() => submit());
});

function submit() {
    localStorage.clear();

    let name = $("#name").val();
    let date = $("#date").val();
    let city = $("#city").val();

    localStorage.setItem("name", name);
    localStorage.setItem("date", date);
    localStorage.setItem("city", city);

    window.location.href='home.html';
}