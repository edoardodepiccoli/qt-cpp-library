# 📚 Qt Library Management System

A comprehensive C++ library management application built with Qt, demonstrating advanced object-oriented programming concepts and design patterns.

## 🎯 Overview

This application serves as a practical implementation of a library management system, showcasing:
- Object-oriented programming principles
- Polymorphism and inheritance patterns
- Qt framework integration
- MVC (Model-View-Controller) architecture
- Visitor design pattern implementation

## 🧪 App Demo

### Search And Index
![Search and Index Demo](https://github.com/edoardodepiccoli/qt-cpp-library/blob/main/demo-gifs/search%20and%20index%20demo.gif)

### Create New Items
![Create New Items Demo](https://github.com/edoardodepiccoli/qt-cpp-library/blob/main/demo-gifs/new%20and%20create%20demo.gif)

### Edit And Update Items
![Edit and Update Items Demo](https://github.com/edoardodepiccoli/qt-cpp-library/blob/main/demo-gifs/edit%20and%20update%20demo.gif)

### Delete Items
![Delete Items Demo](https://github.com/edoardodepiccoli/qt-cpp-library/blob/main/demo-gifs/delete%20demo.gif)

### Resizing Interface
![Resizing Interface Demo](https://github.com/edoardodepiccoli/qt-cpp-library/blob/main/demo-gifs/resizing%20demo.gif)

## 🚀 Getting Started

### 🔨 Building the Application

1. Run the build script:
```bash
./build.sh
```

### 💻 Running the Application

The application can be run in two modes:

1. **GUI Mode** (default):
```bash
./build/bin/.../qt-library
```

2. **CLI Mode** (for testing backend business logic):
```bash
./build/bin/.../qt-library --cli
```

The CLI mode provides a simple command-line interface to test the core functionality without the graphical user interface.

## 🏗️ Architecture

### 🧩 Core Components

The application follows a structured architecture with clear separation of concerns:

- **Models**: Data structures and business logic
- **Views**: User interface components
- **Controllers**: Application flow and state management
- **Visitors**: Implementation of the visitor pattern for type-specific operations
- **CLI**: Command-line interface components
- **Database**: Data persistence layer

### 🧭 Navigation Flow

The application's navigation flow is inspired by RESTful patterns commonly used in web applications (like Ruby On Rails web apps), adapted for a desktop GUI context:

| Action         | View         | View Transition             |
| -------------- | ------------ | --------------------------- |
| List all items | IndexView    | → IndexView                 |
| Show item      | ShowItemView | IndexView → ShowItemView    |
| New item form  | NewItemView  | IndexView → NewItemView     |
| Edit item form | EditItemView | ShowItemView → EditItemView |
| Create item    | NewItemView  | NewItemView → IndexView     |
| Update item    | EditItemView | EditItemView → ShowItemView |
| Delete item    | ShowItemView | ShowItemView → IndexView    |

This pattern provides a clear and intuitive way to navigate between different views while maintaining a consistent user experience.

## ✨ Features

- Complete CRUD operations for library items
- Dynamic form generation based on item type
- Fuzzy search functionality
- Type-safe item management
- Modern Qt-based user interface

## 📊 Development Status

### ✅ Completed Features
- New item creation with dynamic form generation
- Item viewing and detailed information display
- Item editing functionality
- Delete operations
- Search capabilities with fuzzy-like matching

### 🔄 Planned Improvements
- Better UI styling

## 🚨 Project Feedback and Action Steps

- [ ] Fix segmentation fault runtime error when clicking on "View Item", then "New Item"

This error is currently not present on MacOS, only on Ubuntu.

I am currently trying to fix the error, still on my MacOS ARM dev setup.

Here is what I think is happening:
The error was occurring because on Ubuntu (and potentially other Linux distributions), uninitialized pointers can have different default values compared to macOS. By explicitly initializing all pointers to nullptr, we ensure (I hope) consistent behavior across all platforms.

The segmentation fault is/was (probably) happening because:
- currentForm was uninitialized
- When setUpForm was called, it tried to check if (currentForm) which could evaluate to true with garbage memory. By looking at the stack trace provided by valgrind, the problem seems exactly that...
- This led to trying to remove and delete an invalid widget pointer

The VM to test the project for submission is a .ova VM. I will try to check out [this link](https://github.com/utmapp/UTM/discussions/2521) to find out how to emulate it on an ARM-based machine (my M1 MacBook Air) 🤞🏻 (Edit: it didn't work)
- [ ] Improve ShowItemView UI
- [ ] Add option to Upload an Image for each item

This last point is trickier. My idea is to implement it by making it so the user can select an image from their pc in png, jpg or jpeg format. The app then copies it to the asset folder and it sets the item imagePath to the imagePath in the asset folder. This should be taken into account also when performing all other CRUD operations. Do this as soon as the rest of the application is working well.

## 🔧 Technical Details

The application leverages several key design patterns:
- Visitor pattern for type-specific operations
- MVC pattern for clean architecture
- Signal-slot mechanism for Qt-based event handling
- Smart pointer management for memory safety
