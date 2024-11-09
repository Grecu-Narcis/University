# Task Manager

## Description

We need a mobile app that allows users to manage their daily tasks efficiently. The app should let users create, view, edit, and delete tasks easily. It must have a simple and intuitive design so that anyone can use it without difficulty. A clean home screen will display all tasks, and users can quickly add or remove tasks with just a few taps. The app should work on both Android and iPhone devices.

Users should be able to access and use the app even when offline. The focus is on making the app user-friendly and functional for everyday task management.

## Domain

### Entity: **Task**

This app will persist a "Task" entity, which represents a to-do item or activity that users need to manage. Below are the details of each field within the Task entity.

### Fields:

1. **Task ID** (String/Integer)

   - A unique identifier for each task, which helps to distinguish tasks. This field is generated automatically and used internally for managing tasks.

2. **Title** (String)

   - The main name or label for the task (e.g., "Buy groceries"). This is the most important field, as it summarizes what needs to be done.

3. **Description** (String)

   - An optional, more detailed explanation of the task. It can include additional information like steps, notes, or specifics (e.g., "Buy vegetables and fruits from the farmers' market").

4. **Due Date** (Date)

   - The date and time by which the task should be completed. This field helps users track deadlines for their tasks. It can be optional or required, depending on user needs.

5. **Is Completed** (Boolean)

   - A true/false value that indicates whether the task has been completed. Users can mark tasks as done when they finish them.

6. **Priority** (String)
   - This field represents the priority level of the task (e.g., "High," "Medium," or "Low" or as numerical values). It helps users prioritize more important tasks.

### CRUD Operations for the **Task** Entity

#### 1. **Create**

- **Description**: This operation allows the user to create a new task and save it to the system.
- **Required Fields**:
  - **Title**: A name for the task (e.g., "Buy groceries"). This is required for every task.
  - **Optional Fields**:
    - **Description**: Additional details or notes about the task.
    - **Due Date**: The date and time by which the task should be completed.
    - **Priority**: The urgency of the task (e.g., "High", "Medium", "Low").
- **Process**: The user fills in the task details and submits them. The app assigns a unique **Task ID** and saves the task.

#### 2. **Read**

- **Description**: This operation allows users to view all their tasks.
- **Fields Displayed**:
  <!-- - **Task ID**: To identify each task. -->
  - **Title**: The name of each task.
  - **Due Date**: The deadline for the task.
  - **Is Completed**: Indicates whether the task is completed or not.
  - **Priority**: The urgency of the task (e.g., "High", "Medium", "Low").
- **Filtering Options**:
  - **Show Completed Tasks**: Displays only tasks marked as completed.
  - **Show Incomplete Tasks**: Displays only tasks that are still pending.
- **Process**: The app retrieves and displays all tasks. Users can choose to filter the view based on completion status.

#### 3. **Update**

- **Description**: This operation allows users to modify the details of an existing task using an edit button.
- **Process**:
  - Each task displayed has an **Edit** button next to it.
  - When the user clicks the **Edit** button, a new window opens pre-filled with the task's current details.
  - Users can modify any of the fields: **Title**, **Description**, **Due Date**, **Is Completed**, and **Priority**.
  - After making changes, the user saves the updated task, and the app updates the task.

#### 4. **Delete**

- **Description**: This operation allows users to delete a task that is no longer needed, requiring the task name for confirmation.
- **Process**:
  - Each task displayed has a **Delete** button next to it.
  - When the user clicks the **Delete** button, they are taken to a new screen where they must input the task name they want to delete.
  - After entering the task name, the user clicks a **Confirm** button.
  - The app verifies that the inputted task name matches an existing task before proceeding with the deletion.
  - If the names match, the app removes the task from the database; if not, an error message is displayed.

### Persistence Details for the **Task** Entity

#### Local Database Persistence

The local database will persist the following CRUD operations:

1. **Create**

   - **Details**: When a user creates a new task, the task details (Title, Description, Due Date, Is Completed, Priority) are saved in the local database for offline access.

2. **Read**

   - **Details**: Users can read and view all tasks stored in the local database. This allows them to access their tasks even without an internet connection.

<!-- 3. **Update**

   - **Details**: When a user updates a task, the changes are immediately saved to the local database to ensure the latest task details are accessible offline. -->

3. **Delete**
   - **Details**: If a task is deleted, this change is also reflected in the local database to remove the task from the user's view.

#### Server Persistence

The server will persist the following CRUD operations:

1. **Create**

   - **Details**: When a new task is created, it is sent to the server for storage in the central database, ensuring the task is accessible across devices.

2. **Read**

   - **Details**: When online, users can read and retrieve all tasks from the server to get the most current data.

3. **Update**

   - **Details**: When a task is updated, the changes are sent to the server to update the task in the central database, keeping all user devices synchronized.

4. **Delete**
   - **Details**: When a task is deleted, the request is sent to the server to remove the task from the central database, ensuring it no longer appears for the user on any device.

### Summary

- **Local Database**: Create, Read, Delete
- **Server**: Create, Read, Update, Delete
