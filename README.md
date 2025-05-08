# 💪 Qt C++ Library

This is a Qt C++ Library Management app. 
Its main goal is to showcase the programmer's ability to work with C++ OOP concepts, especially polymorphism (💀).

This is to say, I coded this because of a university assignment.

Enjoy :)

---

## 💼 "Back-end" and Business Logic

### Models, Views and Controllers

See models, views and controllers folders.

### Visitors, CLI and db

Same as above, see folder names. Pretty easy to figure out everything.

---

## 🎨 "Front-end" and User Experience

### UX and Navigation Flow

This navitation flow is heavily inspired (aka copied) by the RESTful routing pattern adopted by Ruby On Rails.
I love Ruby On Rails.

| Action         | REST Route          | View Transition             |
| -------------- | ------------------- | --------------------------- |
| List all items | GET /items          | → IndexView                 |
| Show item      | GET /items/:id      | IndexView → ShowItemView    |
| New item form  | GET /items/new      | IndexView → NewItemView     |
| Edit item form | GET /items/:id/edit | ShowItemView → EditItemView |
| Create item    | POST /items         | NewItemView → IndexView     |
| Update item    | PUT /items/:id      | EditItemView → ShowItemView |
| Delete item    | DELETE /items/:id   | ShowItemView → IndexView    |

## TODO

- [x] Create `NewItemView` page  
  - [x] Create an `ItemFormVisitor` that returns different types of form based on the item type  
    - [x] Take inspiration from the `ItemCardVisitor` to handle state  
  - [x] The form sends a signal that triggers a private slot that sends a signal up when it creates a new item  
  - [x] The signal is intercepted by the `NewItemView` class that triggers a private slot that propagates the signal  
  - [x] The signal is intercepted by the `MainWindow` that simply creates the new item
```
How can I differentiate between the various types?  
Maybe create the object at the level of the form returned by the `ItemFormWidget`, then simply pass the pointer up to the parents?  
This could be a decent idea, I hope (it was, I hope, again)
```
- [x] Create a barebone `ViewItemView` (or something with a more decent name, edit: kept this name because it is funny ahah) to display all item's info
- [x] Move delete button to `ViewItemView`
- [x] Add "Edit Item" button to `ViewItemView`

- [x] Create a working `EditItemView`
```
Maybe you could use the same form used by the NewItemView but modifying it a little bit to store a pointer to the item.
Watch out and implement (or not) proper ownership!
When editing item, since Library class does not have anything, simply do this:
- Pass the item to the EditItemView
- Populate the form with its values
  - Do not allow switching type
  - Add update and back buttons
- When clicking back simply send a signal to mainwindow
- When clicking update, find a way to update its fields
- Probably, you should send a Item * to the mainwindow, then call the update method in the Library with it (do all the type checking stuff in it with some sort of cast)
```
- [ ] Create a working search bar at the top of the index view.
```
Make it use a method of the Library for sure. Keep things simple, just create the method that takes a string and returns the results...
Be really careful with pointer ownership tho. This is the tricky part about returning results.
Also, if you want to make things simpler, simply refresh the whole UI of the IndexView from the MainWindow with the updated Library.
```