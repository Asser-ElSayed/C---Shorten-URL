
1. Overview:
This application is designed to deliver a user friendly Shorten URL program which takes a long URL as an input and produces an output of a Readable and Shorter URL. Moreover, the user can give a shortened URL as an input and resolve the URL to the original long URL with perfect timing. Finally, each input is validated against the existing URLs and correct URLs to check the integrity of the input.

2. Workflow of the program:
[System Startup]
|
└── Initialization
* Open data.txt from the File System.
* Load all existing mappings into RAM (std::unordered_map) for speed.
* Retrieve the Global Counter (Last ID used) to maintain sequence.
|
[Main Menu: User Input]
|
├── Option A: Shorten a New URL
| |
| └── Input Validation
| * Check for http:// or https://.
| * Verify presence of domain period (.).
| * Ensure no white space characters.
| * If Invalid: Display Error → Return to Menu.
| |
| └── Duplicate Check
| * Scan Map values for the same Long URL.
| * If Replicated: Display Error → Return to Menu.
| |
| └── The Generation Engine
| 1. Linguistic Algorithm: Strip vowels/process string into a reasonable slug.
| 2. Unpredictable Suffix: Increment Counter → Multiply by Prime "Salt."
| 3. Base62 Encoding: Convert Salted number into a compact 62-bit string.
| 4. Concatenation: Join Slug + "-" + Base62 Suffix.
| |
| └── Persistence & Output
| * Store new mapping in File System (data.txt).
| * Update the Map in RAM.
| * Display Shortened URL to user.
|
└── Option B: Resolve a Short Link
|
└── Format Integrity Check
* Verify input contains the required separator (-).
* Check for reasonable string length.
* If Malformed: Display Error → Return to Menu.
|
└── Map Lookup (RAM)
* Search Map Keys for the provided short link.
* If No Hit: Display 404 Error → Return to Menu.
* If Hit: Display Original Long URL for the user.
|
[System Exit]
|
└── Final Save
* Ensure Global Counter and latest maps are confirmed in the File System.
* Clear RAM and terminate.

