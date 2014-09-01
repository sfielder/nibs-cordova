angular.module('nibs.message', ['ngResource', 'ngSanitize', 'nibs.config'])

    // Routes
    .config(function ($stateProvider) {

        $stateProvider

            .state('app.messages', {
                url: "/messages",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/message-list.html",
                        controller: "MessageListCtrl"
                    }
                }
            })

            .state('app.message-detail', {
                url: "/messages/:messageId",
                views: {
                    'menuContent' :{
                        templateUrl: "templates/message-detail.html",
                        controller: "MessageDetailCtrl"
                    }
                }
            })


    })

    // Resources
    .factory('Message', function ($resource, HOST) {
        return $resource(HOST + 'messages/:id');
    })


    //Controllers
    .controller('MessageListCtrl', function ($scope, Message) {
        $scope.messages = Message.query();

        $scope.doRefresh = function() {
            $scope.messages = Message.query(function() {
                $scope.$broadcast('scroll.refreshComplete');
            });
        }
    })

    .controller('MessageDetailCtrl', function ($state, $scope, $stateParams, $sce, Message) {

        $scope.message = Message.get({id: $stateParams.messageId}, function() {
            $scope.message.htmlMessage = $sce.trustAsHtml($scope.message.message);
        });


        $scope.deleteItem = function() {
            $scope.message.$delete({id: $scope.message.id}, function() {
                $state.go('app.messages');
            });
        };

    });
