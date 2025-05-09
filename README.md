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

Click on the gifs to see them with a better quality

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

## 🔧 Technical Details

The application leverages several key design patterns:
- Visitor pattern for type-specific operations
- MVC pattern for clean architecture
- Signal-slot mechanism for Qt-based event handling
- Smart pointer management for memory safety
