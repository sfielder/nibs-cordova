angular.module('nibs.gallery', ['ngResource', 'nibs.s3uploader', 'nibs.config'])

    // Routes
    .config(function ($stateProvider) {

        $stateProvider

            .state('app.gallery', {
                url: "/gallery",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/gallery.html",
                        controller: "GalleryCtrl"
                    }
                }
            })

    })

    // Resources
    .factory('Picture', function ($resource, HOST) {
        return $resource(HOST + 'pictures/:id');
    })

    //Controllers
    .controller('GalleryCtrl', function ($scope, $rootScope, $ionicPopup, Picture, S3Uploader) {

        $scope.pictures = Picture.query();

        $scope.takePicture = function (from) {

            if (!navigator.camera) {
                $ionicPopup.alert({title: 'Sorry', content: "This device does not support Camera"});
                return;
            }

            var fileName,
                options = {   quality: 45,
                    allowEdit: true,
                    targetWidth: 300,
                    targetHeight: 300,
                    destinationType: Camera.DestinationType.FILE_URI,
                    encodingType: Camera.EncodingType.JPEG };
            if (from === "LIBRARY") {
                options.sourceType = Camera.PictureSourceType.PHOTOLIBRARY;
                options.saveToPhotoAlbum = false;
            } else {
                options.sourceType = Camera.PictureSourceType.CAMERA;
                options.saveToPhotoAlbum = true;
            }

            navigator.camera.getPicture(
                function (imageURI) {
                    // without setTimeout(), the code below seems to be executed twice.
                    setTimeout(function () {
                        fileName = new Date().getTime() + ".jpg";
                        S3Uploader.upload(imageURI, fileName).then(function () {
                            var p = {url: 'https://s3-us-west-1.amazonaws.com/sfdc-demo/' + fileName};
                            var pic = new Picture(p);
                            pic.$save(pic);
                            $scope.pictures.push(p);
                        });
                    });
                },
                function (message) {
                    // We typically get here because the use canceled the photo operation. Seems better to fail silently.
                }, options);
            return false;
        };

    });
