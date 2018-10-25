var QUERY = "panda",
kittenGenerator = {
    searchOnFlickr_: "https://secure.flickr.com/services/rest/?method=flickr.photos.search&api_key=892aaa8ab3cfee5c9674dced5cbbd74f&text=" + encodeURIComponent(
        QUERY) + "&safe_search=1&content_type=1&sort=relevance&per_page=20",
    requestKittens: function () {
        var t = new XMLHttpRequest;
        t.open("GET", this.searchOnFlickr_, !0), t.onload = this.showPhotos_.bind(this), t.send(null)
    },
    showPhotos_: function (t) {
        for (var e = t.target.responseXML.querySelectorAll("photo"), r = 0; r < e.length; r++) {
            var n = document.createElement("img");
            n.src = this.constructKittenURL_(e[r]), n.setAttribute("alt", e[r].getAttribute("title")), document.body
                .appendChild(n)
        }
    },
    constructKittenURL_: function (t) {
        return "http://farm" + t.getAttribute("farm") + ".static.flickr.com/" + t.getAttribute("server") + "/" + t.getAttribute(
            "id") + "_" + t.getAttribute("secret") + "_s.jpg"
    }
};
document.addEventListener("DOMContentLoaded", function () {
    kittenGenerator.requestKittens()
});