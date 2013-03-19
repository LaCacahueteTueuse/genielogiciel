using System.Collections.Generic;
using System.Linq;
using Moq;
using NUnit.Framework;

namespace PeopleFinder
{
    [TestFixture]
    public class PeopleTests
    {
        [Test]
        public void Should_Return_Two_Persons_With_FirstName_John()
        {
            // Setup
            var repository = new PersonRepository();
            var people = new People(repository);

            // Action
            var persons = people.Query(p => p.FirstName == "John");
            
            // Verify the result
            Assert.AreEqual(persons.Count(), 2, "Should return 2 persons with first name John.");
        }

        [Test]
        public void Should_Return_Two_Persons_With_LastName_MacDonald()
    {
        // Setup
        var repository = new PersonRepository();
        var people = new People(repository);

        // Action
        var persons = people.Query(p => p.LastName == "MacDonald");

        // Verify the result
        Assert.AreEqual(persons.Count(), 2 , "Should return 2 persons with last name MacDonald.");
    }
    }
    
}