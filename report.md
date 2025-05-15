## Github Repository

[Github](https://github.com/edoardodepiccoli/qt-cpp-library)

## Quick Description

This project involves developing a fully functional Library Management desktop application using Qt and C++. The app must follow the MVC pattern and support polymorphic behavior using an advanced technique like the Visitor Pattern. The user will be able to perform full CRUD operations on at least three item types (in this particular case they are book, movie, and article) using a simple and user friendly Qt GUI.

All features must comply with the project specifications outlined below.

## Project Specifications (& Final Report Example)

[project specs.pdf](https://res.craft.do/user/full/bbe0b2c6-eedd-70f7-5cd8-bc3021cad315/doc/7D296F6B-89A9-4B3D-92C8-CDE75327E411/E74F8437-EA33-427E-A285-FD2CB849D980_2/qLV6nCyfEe42c1J9KKRYyD9gFgOyrIZdjD0XH1TTRa0z/project%20specs.pdf)

[report example.pdf](https://res.craft.do/user/full/bbe0b2c6-eedd-70f7-5cd8-bc3021cad315/doc/7D296F6B-89A9-4B3D-92C8-CDE75327E411/CCD12E68-75B1-4310-B96D-3BFB488AF481_2/jY25sQhpXp00vLkFXYy94VNW7yk40etjm2261snr5noz/report%20example.pdf)

# Introduction and Project Description

**Qt Library** is a desktop application that lets users quickly and easily categorize their books, movies, and articles through a simple, clean, and intuitive interface. Each item has its own set of attributes.

The project is written in C++ using the Qt framework, which I used for widgets and helpful types like custom strings and JSON classes. It's structured following the MVC pattern and uses the Visitor pattern to handle polymorphism in a non-trivial way.

```
<https://github.com/pde-rent/repo2txt>
+--------------------------------------------+
| Dump tree for directory: qt-library        |
+--------------------------------------------+
├── cli
│  ├── cli.cpp
│  └── cli.h
├── controllers
│  ├── mainwindow.cpp
│  └── mainwindow.h
├── db
│  ├── data.json
│  ├── default_article.png
│  ├── default_book.png
│  ├── default_movie.png
│  └── images
├── main.cpp
├── models
│  ├── article.cpp
│  ├── article.h
│  ├── book.cpp
│  ├── book.h
│  ├── item.cpp
│  ├── item.h
│  ├── library.cpp
│  ├── library.h
│  ├── movie.cpp
│  └── movie.h
├── views
│  ├── edititemview.cpp
│  ├── edititemview.h
│  ├── indexview.cpp
│  ├── indexview.h
│  ├── newitemview.cpp
│  ├── newitemview.h
│  ├── showitemview.cpp
│  └── showitemview.h
└── visitors
   ├── debugvisitor.cpp
   ├── debugvisitor.h
   ├── itemcardvisitor.cpp
   ├── itemcardvisitor.h
   ├── itemformvisitor.cpp
   ├── itemformvisitor.h
   ├── itemshowvisitor.cpp
   ├── itemshowvisitor.h
   ├── jsonvisitor.cpp
   ├── jsonvisitor.h
   └── visitor.h

```

In this, I took a lot of inspiration from the web development framework Ruby on Rails, which uses the RESTful pattern for routing to create a battle-tested, convention-oriented system.

While my project doesn't use routing in the same way (being a desktop app), I applied that same philosophy to how views and features are structured. Every feature is built with that kind of organization in mind, resulting in a consistent structure and user experience. This results in a "routing system" that looks like this:

| Action                 | View         | View Transition              |
| ---------------------- | ------------ | ---------------------------- |
| List all items (INDEX) | IndexView    | → IndexVIew                  |
| Show item (SHOW)       | ShowItemView | IndexView → ShowItemView     |
| New item form (NEW)    | NewItemView  | IndexView → NewItemView      |
| Edit item form (EDIT)  | EditItemView | ShowItemView → EditItemView  |
| Create item (CREATE)   | NewItemView  | NewItemView → IndexView      |
| Update item (UPDATE)   | EditItemView | EditItemView → IndexItemView |
| Delete item (DESTROY)  | ShowItemView | ShowItemView → IndexView     |

I chose this architecture because it's familiar to me from working with Ruby on Rails. I like it, it's low-maintenance and makes for a straightforward user experience.

I also thought that fully embracing the Visitor pattern—for debugging, creating JSON objects, and generating Qt widgets—was a good way to use polymorphism in a modular and interesting way.

# Model

## High-Level Overview

At the core of the application is the `Library` class, which handles all operations related to managing different types of items—Books, Movies, and Articles. The backend is designed to function independently of the graphical user interface, resulting in a loosely coupled and highly maintainable system. For example, to understand or modify how `searchItems(query)` works, one can directly inspect the implementation in the `Library` class without needing to adjust any part of the UI—the views will automatically reflect changes in the logic.

## The Library

The model consists of the following five classes:

- `Library`
- `Item`
- `Book` (inherits from `Item`)
- `Movie` (inherits from `Item`)
- `Article` (inherits from `Item`)

The `Library` class is responsible for all model-level logic. No other component in the application is allowed to modify items directly. This centralized approach simplifies debugging, enforces consistency, and accelerates development and testing.

The class functions as follows:

- It maintains a `std::vector` of `std::unique_ptr<Item>`.
- It provides a complete set of methods for performing CRUD operations, returning appropriate results such as status codes, item pointers, or collections of items.
- The interface is designed to be agnostic to the frontend, supporting both GUI and CLI versions without requiring different behavior for each.

## Data Persistence and the Visitor Pattern

The `Library` class also manages all persistence logic. Data is stored in a local `data.json` file within the `db` folder, along with image paths associated with each item. When a user adds or updates an item with an image, the application creates a local copy of that image. This ensures that the image remains available even if the original file is removed from the user's file system.

This is where the **Visitor Pattern** is applied. A dedicated `JSONVisitor` class is used to serialize items into JSON format. It defines a separate `visit()` method for each item type (Book, Movie, and Article), allowing all items—stored as base `Item` pointers—to be processed polymorphically. This design leads to clean, modular code and helps keep the `Library` class focused on its core responsibilities.

## The Item Class

The `Item` class defines a common interface and set of core attributes shared by all item types:

- `id`
- `title`
- `description`
- `year`
- `review`
- `comment`
- `imagePath`

It includes standard getters and setters for these properties.

## Book, Movie, and Article

These classes inherit from `Item` and extend it with a few specific fields:

- `Book`: adds an `author` field.
- `Movie`: adds a `director` field.
- `Article`: adds both an `author` and a `link` field.

These subclasses are kept minimal, adding only what is necessary for their respective item types.

# View & Controller

## Qt Framework and Initial Challenges

The view layer of the application was, by far, the most challenging part to implement. Initially, I jumped straight into development without much planning, quickly realizing that Qt is a powerful, comprehensive, and feature-rich framework. The documentation is vast, and there are often multiple ways to accomplish the same task.

My first approach was to break the UI into reusable components. For example, I attempted to create a single form component that could be reused for both item creation and editing, with minimal changes. While this made sense in theory, I lacked the experience to implement it effectively—especially when it came to memory management. As a result, I frequently encountered segmentation faults, stemming from improper pointer usage and ownership issues.

After spending over 20 hours on an initial version, I eventually scrapped the entire project out of frustration. I returned to it months later, having studied the Qt framework a little bit better and invested time in planning the architecture before writing any new code.

## Key Architectural Questions

While designing the UI, I encountered a number of foundational questions:

- Where should the core application logic reside—centrally or within individual widgets?
- How should I manage and preserve application state?
- If I pass pointers around to share state, who owns those pointers? Should the `Library` own them? If a form needs to modify an item, should it notify the `MainWindow`?
- How can I effectively manage view changes and ensure that deleted views clean up their widgets properly?
- How should the views integrate the widgets generated by the UI visitors?

These were all important questions that shaped the final design. Below is a breakdown of the view architecture and the solutions I arrived at.

## The View Layer

### MainWindow

The `MainWindow` acts as the Controller in the application. It connects the model (the `Library` class) to all views and UI components. I decided to centralize application state within the `MainWindow` by storing a `std::unique_ptr` to the main `Library` instance. All create, update, and delete operations from the views are routed through the `MainWindow`, ensuring consistent and centralized logic management.

### IndexView

`IndexView` is responsible for listing and searching all items. It uses the `library->searchItems()` method to retrieve results. If the search query is empty, the method returns all items; otherwise, it searches across all relevant attributes and returns matching items. Each item is then passed to an `ItemCardVisitor`, which generates a card widget appropriate to the item type. Clicking on "View" navigates to the `ShowItemView`.

### ShowItemView

`ShowItemView` functions similarly to `IndexView`, with a few key differences:

- It displays a single item instead of a list.
- It uses an `ItemShowVisitor` to generate a detailed display widget for the item.
- It provides action buttons: one for deletion (handled via the `MainWindow`) and one for editing, which navigates to the `EditItemView`.

### EditItemView

The `EditItemView` is straightforward: it receives a pointer to an item and uses an `ItemFormVisitor` to generate the appropriate form for editing. The form is pre-filled with the item's current data, and changes are routed through the `MainWindow`.

### NewItemView

`NewItemView` is slightly more complex. It must dynamically load the appropriate form based on the item type selected by the user. It starts with a default "Book" form. When the user selects a different type from the `QComboBox`, the form is updated accordingly. To avoid memory leaks or dangling pointers, the previously displayed form is explicitly deleted before rendering a new one.

Handling image uploads added an extra layer of complexity. Since this feature was implemented late in development, I chose to handle image path logic directly within `NewItemView` rather than embedding it in the visitor-generated widgets. This made integration easier without significantly compromising modularity.

## The Widgets

At this point, a natural question arises: how do these views actually render the appropriate widgets?

This is where the **Visitor Pattern** plays a critical role.

# Polymorphism & Visitors

## Polymorphism and the Visitor Pattern

A key requirement of the project was to handle polymorphism in a non-trivial way. This meant focusing on future expandability and modularity. The recommended approach to achieve this was through the **Visitor Pattern**.

## The Problem

It would have been far simpler to implement UI-related functionality directly inside each item class. For example, each class (like `Book`, `Movie`, `Article`) could have defined a virtual `getWidget()` method that returned the appropriate UI widget. This approach, while perfectly valid for a small application, tightly couples the model and view layers.

The issue arises when changes are needed—especially UI changes. If models are responsible for generating their own widgets, any UI refactor would require modifications in the core logic. This breaks the separation of concerns and makes the application less maintainable over time.

## The Solution

The Visitor Pattern provides a clean way to decouple the UI logic from the data models. Each item class only needs to implement a single `accept()` method, which takes in a visitor. The visitor then handles the actual logic depending on the item type.

This pattern essentially introduces a middle layer between the model and the view. It allows the UI to evolve independently from the core item logic, which keeps the code modular, clean, and easy to extend.

A visitor works by:

1. Visiting a specific item type (`Book`, `Movie`, or `Article`).
2. Executing logic based on that type.
3. Storing the result (e.g., a widget, JSON object, debug output).
4. Exposing the result via a public method.
5. Letting the view retrieve the result and delete the visitor safely.

### JSONVisitor

This is the simplest visitor. Its purpose is to create a `QJsonObject` for each item, storing all relevant properties. It's mainly used for data persistence and serialization when saving the library to the JSON file.

### DebugVisitor

This visitor was particularly helpful during development. It prints item information using `qDebug()`, which allowed me to easily test the backend and interface with the CLI while debugging and validating data structures.

### ItemCardVisitor

This visitor generates the item cards shown in the `IndexView`. Each card displays basic details about an item along with a "View" button. When clicked, this button emits a signal that is captured and passed through the `IndexView` to the `MainWindow`, which then switches to the appropriate detailed view.

### ItemShowVisitor

This visitor is responsible for creating the detailed view widget for a single item. It checks the item type and includes extra UI elements like the image preview. It also generates two action buttons: **Edit** and **Delete**. These buttons emit signals similar to those in `ItemCardVisitor`, allowing consistent communication with the `MainWindow`.

### ItemFormVisitor

This is the most complex visitor. It builds the form used to either create a new item or edit an existing one. Internally, it conditionally displays one of three different forms based on which `visit()` method is triggered (i.e., `visit(Book*)`, `visit(Movie*)`, or `visit(Article*)`).

On form submission, the visitor constructs a new item instance using the entered data and emits it via a signal. The `MainWindow` catches this signal and passes the item to the `Library`, which either updates or creates the item.

A boolean flag inside the visitor tracks whether the form is being used for creation or editing. This way, the same visitor can handle both scenarios, avoiding redundant code and keeping things simpler to maintain.

---

With this, the MVC architecture and Visitor Pattern integration are complete. Next, we'll look at how data is persisted and retrieved from storage.

# Data Storage and Persistence

## Data Persistence

Data is stored locally in a dedicated `db` folder. This folder contains two key components:

- `data.json`: a JSON file where all item properties and their relative image paths are stored.
- `db.images`: a folder where all images uploaded by the user are saved as working copies.

### How It Works

To ensure that storage remains in sync with the application state, all CRUD operations are handled directly by the `Library` class. This means that every time an item is created, updated, or deleted, the changes are automatically persisted to storage through internal methods in the `Library`. As a result, views and UI components don't need to worry about saving or syncing—they simply interact with the `Library`, which acts as the backend for the entire application.

### Handling Images

When a user uploads an image, the app copies it into the `db.images` folder. This ensures that even if the original file is deleted from the user's computer, the app still retains a local copy. If no image is provided during item creation, a default image is automatically assigned based on the item type (book, movie, or article). These default images are bundled with the app inside the `db` folder and cannot be removed, ensuring visual consistency.

### File Operations

The persistence logic is encapsulated in two main methods within the `Library` class:

- `loadFromFile()`: loads the existing data from `data.json` at startup.
- `saveToFile()`: saves the current state of the library to `data.json`.

By calling `loadFromFile()` during initialization and `saveToFile()` after any data-changing operation, the app maintains a consistent, up-to-date state with minimal effort required from the UI layer.

This approach helped me keep the UI logic simpler and more focused, since I didn't have to constantly manage or track the save logic within each view. The separation of concerns made the app more maintainable and allowed me to design the front end with fewer distractions.

## Import/Export Functionalities

The application supports importing and exporting items through both the GUI and CLI interfaces. This feature was implemented to allow users to easily share their libraries or create backups of their data.

### Implementation Details

The import/export functionality is implemented directly in the `Library` class, maintaining the separation of concerns and keeping the model layer responsible for all data operations. The implementation handles both the items and their associated images, ensuring that:

- During import, relative image paths are properly resolved against the import file's location
- During export, images are copied to a dedicated `images` subdirectory
- Image paths in the exported JSON are updated to be relative to the export directory
- Default images are preserved and not accidentally deleted

### GUI Integration

In the GUI, import/export functionality is accessible through the toolbar, with two buttons:
- **Import Items**: Opens a file dialog to select a JSON file
- **Export Items**: Opens a directory dialog to select where to export

The implementation follows the same pattern as other GUI features:
1. User interaction is handled by the `MainWindow` controller
2. The controller uses Qt's native file dialogs for a consistent user experience
3. After successful import/export, the user is notified with a confirmation message
4. The view is automatically refreshed after import to show new items

### CLI Integration

The CLI version provides the same functionality through two commands:
- `import`: Prompts for a JSON file path and imports the items
- `export`: Prompts for a directory path and exports the items

This maintains consistency between the GUI and CLI interfaces, allowing users to work with either interface based on their preference.

### Data Structure

The export process creates a standardized directory structure:
```
export_dir/
├── data.json
└── images/
    ├── image1.png
    ├── image2.jpg
    └── ...
```

This structure ensures that:
- The JSON file and images are kept together
- Relative paths in the JSON file remain valid
- The structure is consistent across different exports
- The exported data can be easily imported back into the application

### Error Handling

The implementation includes basic error handling to ensure a smooth user experience.

This feature completes the application's data management capabilities, allowing users to easily share and backup their libraries while maintaining the application's clean architecture and separation of concerns. I thought this was the best way to implement this feature at this point of development.

---

With all of this in mind, let's now talk about the User Flow, the UI and the User Experience

# User Flow, UI/UX

## User Interface and UX Flow

See the [Demo Video](https://youtu.be/ywMM5f5HGdE) (DOES NOT INCLUDE IMPORT/EXPORT FUNCTIONALITIES SHOWCASE)

When the application launches, the user is greeted with a clean and minimal interface: a blank screen with a search bar at the top, and two main toolbar buttons—**New Item** and **Index**.

If the user wants to add a new entry, they simply click **New Item** and are presented with a form to input the relevant details. To browse existing entries, they click **Index**, which displays a searchable list of all saved items.

Once the database contains data, the user can navigate through items using a flow inspired by conventional RESTful design. The search bar enables real-time filtering of all items. Clicking on **View** next to any entry opens the **Show Item View** for that specific item (whether it's a book, movie, or article).

### Show Item View

This view displays the selected item in more detail:

- On the **left**, the item's image is shown.
- On the **right**, at the top, are all relevant details (title, year, description, etc.).
- Below that, two buttons are provided:
    - **Edit**: navigates to the Edit Item View.
    - **Delete**: removes the item and returns the user to the Index.

### Edit Item View

The **Edit View** is very similar to the New Item form, with one main difference: the user cannot change the item's type. They can, however, modify any of the other properties and click the appropriate **Update** button. After updating, the user is returned to the Index view.

### Image Upload

To add or update an image, the user simply clicks an upload button within the form. A file dialog appears, allowing them to select an image. The application then stores a working copy of the selected image to ensure it remains available, even if the original file is deleted from the user's device.

### Design Philosophy

The navigation flow is intentionally simple and intuitive. There is only **one way** to perform each major action, minimizing confusion and keeping both the development and user experience consistent and maintainable. The interface avoids unnecessary toolbars or redundant buttons.

While a polished UI was not a project requirement, I still aimed to keep it as clean and readable as possible. The result is not flashy, but it is functional, clear, and easy to use.

# Total Work Hours

## Total Estimated Time: ~60 hours

The project was initially scoped for about 40 hours, but due to the steep learning curve with Qt, memory management in C++, and scrapping the first attempt, the real total went well beyond that. Still, the end result is a modular application that I fully understand.

| **Topic**                                     | **Hours**              | **Description**                                                                |
| --------------------------------------------- | ---------------------- | ------------------------------------------------------------------------------ |
| **Scrapped First Version**                    | 15 hours               | Initial full build attempt; ultimately discarded, but some backend reused.     |
| **Backend Logic**                             | 4 hours                | Core logic: Library class, Item types, and main structure (excluding storage). |
| **Planning (Qt, UI/UX)**                      | 1–2 hours              | Project design, structure planning, and defining user interaction flow.        |
| **C++ Virtual Refresher**                     | 1–2 hours              | Quick review of virtual methods and polymorphism essentials.                   |
| **Storage + JSON & Debug Visitors**           | 4 hours                | Persistent data storage system and basic visitors for debug/output.            |
| **Command Line Interface**                    | 3 hours                | CLI layer to interact with and test backend components.                        |
| **MainWindow + Qt Research**                  | 2 hours                | Built initial MainWindow and explored Qt widget system and APIs.               |
| **Views + Visitors (Index, Show, Edit, New)** | 16 hours (~4 per view) | All major UI views with their corresponding visitor classes.                   |
| **Debugging & Refactoring**                   | 6 hours                | Memory management fixes, segmentation fault resolution, general cleanup.       |
| **Image Upload + Path Logic**                 | 3 hours                | Integrated image selector and implemented fallback/default image logic.        |
| **Code Cleanup for Maintainability**          | 1 hour                 | Structural refactor for clarity and reuse.                                     |
| **Final Report Writing**                      | 3 hours                | Documentation of project structure, decisions, and outcomes.                   |

# Lessons Learned

## Qt-Specific Takeaways

- **Qt provides helpful defaults:** Qt automatically prevents the deletion of null widgets and cleans up child widgets when the parent is deleted. These default behaviors reduce the risk of memory errors and simplify memory management.
- **Plan before coding:** Qt is a large and powerful framework. I learned the hard way that taking time upfront to explore its components and tools would have saved me development time and reduced unnecessary complexity later on.

## C++ Language Insights

- **C++ virtual methods are essential:** What seemed like unnecessary complexity in theory turned out to be fundamental for enabling polymorphism and flexibility in the application architecture.
- **Memory management is 50% of the job:** Getting memory management right—avoiding dangling pointers and using clear ownership conventions—is key to writing reliable C++ applications.
- **Smart pointers are the way to go:** `unique_ptr` and `shared_ptr` greatly simplified memory ownership logic. I'll use them as a default in future projects to reduce manual memory handling.
- **Pointers become manageable with practice:** Once understood, pointer logic is a powerful way to manage objects efficiently, especially when keeping object lifetimes predictable and controlled.
- **Platform differences matter:** On macOS, uninitialized pointers often default to `nullptr`, but on Ubuntu, they can point to garbage memory, causing hard-to-diagnose bugs. This taught me to always initialize pointers to `nullptr` explicitly.

## Design & Architecture

- **RESTful patterns are helpful even outside the web:** Using REST-style naming and flow patterns brought clarity to view routing and helped maintain modularity across the UI components.

## General Reflection

- **It took longer than expected, but was worth it:** Although the project exceeded the estimated 40 hours, it significantly deepened my understanding of both Qt and C++. The extra time spent learning was a worthwhile investment.