# Greeting-Services
This repo will show how to add custom services action to update,delete,create &amp; publish D7 Content type

On cloning this repo we will get two modules. One is our custom module "mycorp-greeting" which is managing the Drupal 7 Content type Create,Update,Index,Edit,Delete & Publish option within various Json requests, The Another module "greeting" is a feature module which is managing all the fetures required for the working of services. This includes the Greeting Content type creation and End points for the Services.


How to use the this Modules ?.

Download/Clone the repository.

Add the mycrop-greeting modules inside the modules folder.

Folder path : sites/all/module/custom/mycrop-greeting

Add the greeting features module inside modules feature folder

Folder path : sites/all/module/features/greeting

Once the mycorp-greeting module is enabled, Run update.php to install the feature module greeting. Once everything is done move to admin page "admin/structure/services" there we can find our new services. Edit the service and check everything is enable within our custom services.

Create few contents for the new content type and use the below url to check the services functionality.

 1. /api/v1/greetings - GET 
    Return the list of greetings.
  2. /api/v1/greetings/{greetingID} - GET
    Return a specific greeting of given id.
  3. /api/v1/greetings - POST
    Creates a new greeting. 
    
    Test Json sample used to check the Creation 
    {
      "nid": "35",
      "title": "Greeting Text Content Title",
      "field_greeting_title": "Lorum Ipsum",
      "field_greeting_image": "https://www.powercms.in/sites/default/files/balance-865091_1920.jpg"
    }
    
  4. /api/v1/greetings/{greetingID} - PUT
    Updates an existing greeting.
    
    Test json sample for update
     {
      "nid": "35",
      "title": "The new updated Title",
      "field_greeting_title": "The new updated Greeting Title",
      "field_greeting_image": "https://dummyimage.com/600x400/000/fff"
    }
    
  5. /api/v1/greetings/{greetingID} - DELETE
    Delete an existing greeting.
  6. /api/v1/greetings/{greetingID}/publish - POST
    Publish/unpublish a greeting of given id
    
    Get Functionality will be accessible within our Browser itself, For the Post and Put use the Postman Extension.
    
    
