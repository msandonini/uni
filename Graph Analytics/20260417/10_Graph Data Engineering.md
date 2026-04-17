As we saw, graphs can be used to create views on top of a master dataset (batch layer) or real-time (speed layer) representations of part of the data available.
In that approach, the transactional data resides in the master dataset. That option is useful when we can query and perform analysis on aggregated data.
Other types of analysis, however, cannot be performed on an aggregate version of the data.
Such algorithms require more detailed information to be effective, as they need access to fine-grained version of the data to accomplish their job.

For this type of algorithms using graphs gives us some advantages:
- Multiple data sources, such as geographical or GPS information, social network data, user personal profiles, family data, and the like, can be merged in a single connected source of truth.
- Existing data can be extended with external sources of knowledge (shop locations, people’s addresses, and so on) or with contextual information (a new shop, other complaints, and the like) that can be used to improve the analysis.
- The same data model can support several analysis techniques (for example, to uncover a fraud ring)
- Data can be visualized as a graph to speed the manual analysis. The analysis can be extended to multiple levels of interaction, considering multiple hops.
- The structure simplifies the merging and cleaning operation, thanks to the flexible access pattern provided by the graph model.

The graph represents the main source of knowledge for the merged, cleaned, and extended data, on top of which the analysis is performed and based on which any decisions are taken.
The graph plays the role of master dataset and is the foundation for master data management (MDM), the practice of identifying, cleaning, storing, and governing data [^1].

The key concerns of MDM include:
- Managing changes over time as organizational structures change, businesses merge, and business rules evolve
- Incorporating new sources of data
- Supplementing existing data with external data sources
- Addressing the needs of reporting, compliance, and business intelligence consumers
- Versioning data as its values and schema change

MDM is not an alternative or modern version of data warehousing (DW), although the two practices have a lot in common.
- DW relates to the storage of historical data
- MDM deals with current data

An MDM solution contains the current and complete information for all business entities within a company.
![[Pasted image 20260417115820.png]]

Looking at big data applications from a pure data storage perspective, the main Vs challenges are
- Volume
	- The volume of the data involved is so large that it is hard to store the data on a single machine.
- Velocity
	- A single machine can serve only a limited number of concurrent users.
- Sharding
	- A large dataset is split, and subsets are distributed across several shards on different servers.



---

[^1]: Robinson et al., 2015
