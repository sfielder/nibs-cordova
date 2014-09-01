angular.module('nibs.store-locator', ['ngResource', 'nibs.config'])

    // Routes
    .config(function ($stateProvider) {

        $stateProvider

            .state('app.store-locator', {
                url: "/store-locator",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/store-locator.html",
                        controller: "StoreLocatorCtrl"
                    }
                }
            });

    })

    // Resources
    .factory('Store', function ($resource, HOST) {
        return $resource(HOST + 'stores/:id');
    })

    //Controllers
    .controller('StoreLocatorCtrl', function ($scope, Store) {

        var map,
            currentPosMarker,

            icon = L.icon({
                iconUrl: 'img/leaf-green.png',
                shadowUrl: 'img/leaf-shadow.png',
                iconSize:     [38, 95], // size of the icon
                shadowSize:   [50, 64], // size of the shadow
                iconAnchor:   [22, 94], // point of the icon which will correspond to marker's location
                shadowAnchor: [4, 62],  // the same for the shadow
                popupAnchor:  [-3, -76] // point from which the popup should open relative to the iconAnchor
            });

        $scope.stores = Store.query(function() {
            for (var i=0; i<$scope.stores.length; i++) {
                var store = $scope.stores[i];
                L.marker([store.latitude, store.longitude], {icon: icon}).addTo(map);
            }
        });

        $scope.getLocation = function() {
            map.locate({setView: true, maxZoom: 16});
        };

        setTimeout(function () {
            // create a map in the "map" div, set the view to a given place and zoom
            map = L.map('map', {zoomControl: false}).setView([37.7958340, -122.3940350], 14);

            L.tileLayer('http://server.arcgisonline.com/ArcGIS/rest/services/World_Street_Map/MapServer/tile/{z}/{y}/{x}',
                {detectRetina: true,
                    minZoom: 1,
                    maxZoom: 17,
                    attribution: 'Tiles &copy; 2014 esri.com'}).addTo(map);

            map.on('locationfound', onLocationFound);
            $scope.getLocation();

        });

        $scope.showLocation = function(position) {
            map.panTo(position);
        }

        function onLocationFound(e) {
            var pos = e.latlng;
            console.log(pos);
            if (!currentPosMarker) {
                currentPosMarker = L.marker(pos).addTo(map);
            } else {
                currentPosMarker.setLatLng(pos);
            }
            $scope.showLocation(pos);
        }

    });