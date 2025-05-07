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

| Action            | REST Route           | View Transition                 |
|-------------------|----------------------|---------------------------------|
| List all items    | GET /items           | → IndexView                     |
| Show item         | GET /items/:id       | IndexView → ShowItemView        |
| New item form     | GET /items/new       | IndexView → NewItemView         |
| Edit item form    | GET /items/:id/edit  | ShowItemView → EditItemView     |
| Create item       | POST /items          | NewItemView → IndexView         |
| Update item       | PUT /items/:id       | EditItemView → ShowItemView     |
| Delete item       | DELETE /items/:id    | ShowItemView → IndexView        |

## TODO

- create newitemview page
    - create an itemformvisitor that returns different types of form based on the item type
        - take inspiration from the itemcardvisitor to handle state
    - the form sends a signal that triggers a private slot that sends a signal up when it creates a new item
    - the signal is intercepted by the newitemview class that triggers a private slot that propagates the signal
    - the signal is intercepted by the mainwindow that simply creates the new item
    - how can i differentiate between the various types?
    - maybe create the object at the level of the form returned by the itemformwidget, then simply pass the pointer up to the parents?
    - this could be a decent idea, i hope