1. Project Title

Interactive Expense Tracker (Web-Based Application)

2. Objective

To build a simple, user-friendly web application that helps users record, manage, and analyze daily expenses.

Provide an intuitive UI for adding, viewing, sorting, and summarizing expenses.

3. Key Features
(A) Add Expense

A popup modal form is used to enter:

Category

Amount

Date

Uses basic validation to ensure all fields are filled.

(B) Store Data Permanently

Expenses are saved in localStorage, so the data remains even if the page is refreshed.

(C) View All Expenses

Expenses are displayed in a clean, responsive table.

Each entry shows Category, Amount, and Date.

(D) Filter by Category

User can type a category name.

Displays only matching expenses.

Helps in checking category-specific spending (e.g., Food, Travel).

(E) Sorting Options

Users can sort expenses based on:

Amount (High → Low)

Amount (Low → High)

Date (Newest → Oldest)

Date (Oldest → Newest)

(F) Summary / Total Calculation

Total Spend → Shows total of all expenses combined.

Category-wise Summary → Shows the total spent per category.

4. Tools & Technologies Used
Frontend


Google Fonts (Poppins) → Modern typography

Storage

Browser’s LocalStorage

Stores data in JSON format

Enables persistence without backend

5. How the Application Works (Workflow)

User clicks "+ Add Expense"

Modal form opens → user enters data → submits

JavaScript stores the data inside localStorage

The table is updated dynamically

User can:

Filter

Sort

View totals

View category-wise summaries

Summary card displays results at the bottom

6. JavaScript Logic (Core Concepts Used)

Event Listeners for form submission & button clicks

DOM Manipulation (querySelector, innerHTML)

Array Methods:

push() – add data

filter() – filter by category

reduce() – totals

sort() – sorting by amount/date

JSON Handling:

JSON.stringify() → store array in localStorage

JSON.parse() → retrieve stored data

Spread Operator ([...]) for safe sorting without mutating original data

7. UI/UX Enhancements

Animated gradient background

Sticky header

Hover animations for buttons & rows

Glassmorphism modal effect

Responsive layout for mobile

Smooth transitions and shadows

8. Advantages of the Project

Works offline

No backend required

Lightweight and fast

Easy to use

Good real-life utility

Demonstrates strong frontend development skills

9. Real-world Use Cases

Daily pocket expense tracking

Student spending manager

Small trip budget tracking

Home or family budgeting
