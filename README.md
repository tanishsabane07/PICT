# Employee Management Lightning App

## Aim
To develop an Employee Management Lightning App in Salesforce with proper field validations.

---

# Requirements

The system validates:
- Employee Name must contain at least 3 characters.
- Employee ID must be unique and greater than 0.
- Salary must be between 10,000 and 500,000.
- Email must be valid.
- Department must be selected.
- Joining Date cannot be future date.

---

# Step 1: Create Employee Object

Navigate to:

Setup → Object Manager → Create → Custom Object

| Property | Value |
|---|---|
| Label | Employee |
| Object Name | Employee |
| Record Name | Employee Name |

Save the object.

---

# Step 2: Create Fields

Navigate to:

Object Manager → Employee → Fields & Relationships → New

## Fields

| Field Name | Data Type |
|---|---|
| Employee ID | Number (Unique, Required) |
| Salary | Currency |
| Email | Email |
| Department | Picklist |
| Joining Date | Date |

### Department Picklist Values

```text
HR
Finance
IT
Marketing
Sales
Operations
```

---

# Step 3: Create Validation Rules

Navigate to:

Object Manager → Employee → Validation Rules → New

## Employee Name Validation

```apex
LEN(Name) < 3
```

---

## Employee ID Validation

```apex
Employee_ID__c <= 0
```

---

## Salary Validation

```apex
OR(
Salary__c <= 10000,
Salary__c >= 500000
)
```

---

## Department Validation

```apex
ISBLANK(TEXT(Department__c))
```

---

## Joining Date Validation

```apex
Joining_Date__c > TODAY()
```

---

# Step 4: Create Lightning App

Navigate to:

Setup → App Manager → New Lightning App

App Name:
```text
Employee Management App
```

---

# Step 5: Create Employee Tab

Navigate to:

Setup → Tabs → New → Custom Object Tabs

Select:
- Employee Object

Save the tab.

---

# Step 6: Add Tab to App

Navigate to:

Setup → App Manager → Employee Management App → Edit

Add:
- Employees

Save the app.

---

# Result

Successfully developed an Employee Management Lightning App in Salesforce with proper validations for employee records.
