# xv6-x86-kernel-extensions

## About

I enjoy learning about Operating Systems (OS) through hands-on experimentation. This repo hosts my kernel extensions to the MIT xv6/x86 OS. Below is what I've accomplished so far:

- **Implemented `getLCADistance` System Call** (identifier 22 in `syscall.h`) and `test_getLCADistance.c` to validate correct functionality.

  This syscall takes two process IDs (`pid1` and `pid2`) and calculates the graph distance (number of tree hops, or edges) between them passing through their Lowest Common Ancestor (LCA) in the process hierarchy.

  ### Return Code Specification

  <table>
    <thead>
      <tr>
        <th align="center">Return Code</th>
        <th align="left">Meaning</th>
        <th align="left">Description</th>
      </tr>
    </thead>
    <tbody>
      <tr>
        <td align="center"><b>0</b></td>
        <td>Same Process</td>
        <td>Both <code>pid1</code> and <code>pid2</code> are identical (<code>pid1 == pid2</code>).</td>
      </tr>
      <tr>
        <td align="center"><b>&gt; 0</b></td>
        <td>Tree Hops</td>
        <td>Total hops through a shared application ancestor (e.g., direct parent-child is 1, siblings are 2).</td>
      </tr>
      <tr>
        <td align="center"><b>-1</b></td>
        <td>init Boundary</td>
        <td>The Lowest Common Ancestor is <code>init</code> (PID 1), indicating no shared application lineage.</td>
      </tr>
      <tr>
        <td align="center"><b>-2</b></td>
        <td>Invalid PID</td>
        <td>Either <code>pid1</code> or <code>pid2</code> does not exist in <code>ptable</code>.</td>
      </tr>
      <tr>
        <td align="center"><b>-3</b></td>
        <td>Broken Tree</td>
        <td>Traversal ended without reaching <code>init</code> or a common match (fallback for undefined behavior).</td>
      </tr>
    </tbody>
  </table>

## Usage

You can boot up this extended version of xv6 inside the QEMU open source machine emulator and virtualizer.

### Prerequisites and Setup

To build and run xv6 on your machine, you need a 32-bit ELF cross-compiler toolchain (`i686-elf-gcc` or `i386-elf-gcc`) and `qemu-system-i386`.

#### macOS (via Homebrew)

1. Install the toolchain directly using Homebrew:

   ```bash
   brew install i686-elf-binutils i686-elf-gcc qemu
   ```

2. Clone the repository and enter the directory:

   ```bash
   git clone https://github.com/FaroukGhodhbane/xv6-x86-kernel-extensions.git
   cd xv6-x86-kernel-extensions
   ```

3. Build and launch inside QEMU:
   ```bash
   make qemu-nox
   ```

#### Linux (Ubuntu/Debian)

1. Install the build dependencies:

   ```bash
   sudo apt update
   sudo apt install build-essential gdb-multiarch qemu-system-x86 gcc-multilib
   ```

2. Clone and run:
   ```bash
   git clone https://github.com/FaroukGhodhbane/xv6-x86-kernel-extensions.git
   cd xv6-x86-kernel-extensions
   make qemu-nox
   ```

### Running the Tests

Inside the booted xv6 shell:

- **Run all tests:**

  ```bash
  $ test_getLCADistance
  ```

  or

  ```bash
  $ test_getLCADistance 0
  ```

- **Run a specific test case (1–6):**
  ```bash
  $ test_getLCADistance 3
  ```

To exit QEMU at any time, press `Ctrl+A`, release the keys, and then press `X`.

## Learn More

- For the original MIT README, please see [README](README).
- For the MIT xv6 License, please see [LICENSE](LICENSE).
