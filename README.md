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

- change view button to delete button
- make it work

- create newitemview page
    - create a formvisitor that returns different types of form based on the item type
    - do not overcomplicate it or abstract it too much