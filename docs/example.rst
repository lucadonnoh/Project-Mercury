###############################
Introduction to Smart Contracts
###############################

.. _simple-smart-contract:

***********************
A Simple Smart Contract
***********************

Let us begin with a basic example that sets the value of a variable and exposes
it for other contracts to access. It is fine if you do not understand
everything right now, we will go into more detail later.

Storage Example
===============

::

    // SPDX-License-Identifier: GPL-3.0
    pragma solidity >=0.4.16 <0.8.0;

    contract SimpleStorage {
        uint storedData;

        function set(uint x) public {
            storedData = x;
        }

        function get() public view returns (uint) {
            return storedData;
        }
    }

The first line tells you that the source code is licensed under the
GPL version 3.0. Machine-readable license specifiers are important
in a setting where publishing the source code is the default.